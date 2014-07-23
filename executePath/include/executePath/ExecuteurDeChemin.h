#ifndef _EXECUTEUR_DE_CHEMIN_HEADER_
#define _EXECUTEUR_DE_CHEMIN_HEADER_ 
/*==========  Includes  ==========*/

#include "ros/ros.h"

#include "robotino_local_move/LocalMoveAction.h"
// #include "RobotinoLocalMoveClient.h"

#include "rbqt_pathfinder/AstarPath.h"
#include "executePath/EdCState.h"
#include "executePath/command.h"

#include <actionlib/client/simple_action_client.h>
#include <tf/transform_datatypes.h>
#include <std_msgs/Bool.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/Odometry.h>
#include <cmath>
#include <list>
#include <boost/thread.hpp>

//nettoyage à faire dans les #include

/*==========  DEFINES  ==========*/

#ifndef M_PI
    #define M_PI 3.14159265359
#endif
#define NB_MAX_PATH_SAVED 10
#define  sucess actionlib::SimpleClientGoalState::SUCCEEDED

/*==========  Types  ==========*/

typedef executePath::command::Request Request;

/*==========  DECLARATIONS - main.cpp  ==========*/

void odomCallback(nav_msgs::Odometry odom);
void bumperCallback(std_msgs::Bool bumper);
void pathfinderCallback(rbqt_pathfinder::AstarPath pathFound);
bool serviceCallback(executePath::command::Request &req, executePath::command::Response &res);// Called once when the goal completes
void doneCb(const actionlib::SimpleClientGoalState& state,
            const robotino_local_move::LocalMoveResultConstPtr result);
// Called once when the goal becomes active
void activeCb();
// Called every time feedback is received for the goal
void feedbackCb(const robotino_local_move::LocalMoveFeedbackConstPtr feedback);
// Thread d'execution du chemin
void executePath_thread();float calculateRotationNeeded(float startX, float startY, float endX, float endY);
float calculateForwardDisplacementNeeded(float startX, float startY, float endX, float endY);

/*==========  DECLARATIONS - ExecuteruDeChemin.cpp  ==========*/

bool findPath(rbqt_pathfinder::AstarPath &pathFound, std::list<rbqt_pathfinder::AstarPath> listOfPath, int ID);
bool checkServer(actionlib::SimpleActionClient<robotino_local_move::LocalMoveAction> &client);
// void send(robotino_local_move::RobotinoLocalMoveClient client, robotino_local_move::LocalMoveGoal goal);

#endif  // _EXECUTEUR_DE_CHEMIN_HEADER_

/*=================================
=            Main Save            =
=================================*/

/*
    // Pour envoyer des goals au robotino_lcal_move_server
    RobotinoLocalMoveClient rlmc;

    // if( rlmc.checkServer() )
    // {
    //  rlmc.sendGoal( goal );
    //  rlmc.spin();
    // }

    bool almostFinished;
    int dernier = 0;
    
    //Initialisation du noeud ROS
    ros::init(argc, argv, "executeur_de_chemin");
    ros::init(argc, argv, "EdCState");
    
    ros::NodeHandle n;
    
    //Souscription aux topics utiles
    ros::Subscriber odom = n.subscribe("/odom", 1000, odomCallback);
    ros::Subscriber path = n.subscribe("/pathFound", 10, pathfinderCallback);
    
    //Création d'un topic d'état EdCState
    ros::Publisher EdCState_pub = n.advertise<executePath::EdCState>("EdCState", 1000);
    
    //Création d'un service "command"
    ros::ServiceServer service = n.advertiseService("command");
    
    //Récupération de la commande du manager
    // executeurDeChemin::command::Request  &req;
    // int ID = service.req.ID;
    
    // //Recupération du chemin correspondant dans la liste de chemins enregistrés
    // nav_msgs::Path pathToFollow;
    // if (findPath(pathToFollow, listOfPath, ID))
    // {
    //  executeurDeChemin::command::Response accepted = true;
    // }

    ros::Rate loop_rate ( 30 );
    while(n.ok())
    {
        
        //Parcours du chemin
        while (dernier < pathToFollow.poses.size())
        {
            EdCState_pub.publish(EdCState.IN_PROGRESS);
            
            while  (client.getState() != succes)
            {   
                if (service.req.type == service.req.EXECUTE_PATH ||
                    service.req.type == service.req.RESUME)
                {
                    //pose à atteindre
                    float goal_x    = pathToFollow.poses[i].pose.position.x;
                    float goal_y    = pathToFollow.poses[i].pose.position.y;
                    float goal_phi  = tf::getYaw(pathToFollow.poses[i].pose.orientation);
                
                    float dx        = goal_x - current_x;
                    float dy        = goal_y - current_y;
                    float dphi      = atan(dx/dy) - current_phi;
                    
                    float tolerance     = 0.01;     //au cm près
                    float tolerancePhi  = PI/90;    //à 2° près
                
                    //On dirige l'avant du robot vers le point à atteindre
                    robotino_local_move::LocalMoveGoal rotation;
                    
                    rotation.move_x             = 0.0;
                    rotation.move_y             = 0.0;
                    rotation.rotation           = dphi * 180 / PI;      //en °
                    rotation.ignore_rotation    = false;
                    
                    //on crée le client pour envoyer la rotation
                    RobotinoLocalMoveClient client;
                    
                    //on envoie la rotation
                    send(client, rotation);
                
                    //puis on déplace le robot sur x avec la mesure de l'hypoténuse
                    if (client.getState() != succes)
                    {
                        robotino_local_move::LocalMoveGoal goal;
                        
                        goal.move_x = sqrt (dx*dx + dy*dy);
                        goal.move_y = 0.0;
                        goal.rotation = 0.0;
                        goal.ignore_rotation = true;
                    
                        send(client, goal);
                    }
                }
            }
            
            dernier = i;        //on mémorise la dernière pose à chaque fois
                                //au cas où le manager fait pause
        }
    
        //Dernière pose refaite par sécurité
        goal_x      = pathToFollow.poses[dernier].pose.position.x;
        goal_y      = pathToFollow.poses[dernier].pose.position.y;
        goal_phi    = tf::getYaw(pathToFollow.poses[dernier].pose.orientation);
                
        dx          = goal_x - current_x;
        dy          = goal_y - current_y;
        dphi        = goal_phi - current_phi;
                
        goal.move_x = dx;
        goal.move_y = dy;
        goal.rotation = dphi;
        goal.ignore_rotation = false;
        
        bool poseOK = ( client.getState() == succes &&
                        abs(dx) <= tolerance &&
                        abs(dy) <= tolerance &&
                        abs(dphi) <= tolerancePhi);
                

        // Publish
        executePath::EdCState EdCState_msg;
        if (poseOK)
        {
            EdCState_msg.state = EdCState.FINISHED;
        }
        else
        {
            EdCState_msg.state = EdCState.PROBLEM;
        }           
        EdCState_pub.publish(EdCState_msg);

        // Spin
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;*/

/*-----  End of Main Save  ------*/

