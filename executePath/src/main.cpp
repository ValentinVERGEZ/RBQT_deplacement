/*==========  Includes  ==========*/

#include "executePath/ExecuteurDeChemin.h"

/*==========  Global Variables  ==========*/

std::list<rbqt_pathfinder::AstarPath> listOfPath;
rbqt_pathfinder::AstarPath pathToFollow;
executePath::EdCState EdCState_msg;

	// Odométrie
	float current_x		= 0.0;
	float current_y		= 0.0;
	float current_phi = 0.0;

/*============================
=            Main            =
============================*/


int main(int argc, char** argv)
{

	//Initialisation du noeud ROS
	ros::init(argc, argv, "executeur_de_chemin");
	
	ros::NodeHandle n;
	
	//Souscription aux topics utiles
	n.subscribe("/odom", 1000, odomCallback);
	n.subscribe("/pathFound", 10, pathfinderCallback);
	
	//Création d'un topic d'état EdCState
	ros::Publisher EdCState_pub = n.advertise<executePath::EdCState>("EdCState", 1000);
	
	//Création d'un service "command"
	ros::ServiceServer service = n.advertiseService("command", &serviceCallback);

	//Init message
	EdCState_msg.state = executePath::EdCState::LIBRE;

	ros::Rate loop_rate ( 30 );
	while(n.ok())
	{
		// Publish
		EdCState_pub.publish(EdCState_msg);

		// Spin
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}


/*-----  End of Main  ------*/

/*========================================
=            Others Functions            =
========================================*/

void odomCallback(nav_msgs::Odometry odom)
{
	current_x		= (odom).pose.pose.position.x;
	current_y		= (odom).pose.pose.position.x;
	current_phi	= tf::getYaw((odom).pose.pose.orientation);
	
	//ROS_INFO("I am at this point: [%f, %f] with the angle %f rad (%f deg)", current_x, current_y, current_phi, current_phi*180/PI);
}

void pathfinderCallback(const rbqt_pathfinder::AstarPath pathFound)
{
	listOfPath.push_back(pathFound);
	
	if(listOfPath.size() > NB_MAX_PATH_SAVED)
   	{
   		listOfPath.pop_front();
   	}
}

bool serviceCallback(executePath::command::Request  &req,
        executePath::command::Response &res)
{
	// Type
// 	uint8 EXECUTE_PATH = 0
// uint8 PAUSE	= 1
// uint8 RESUME = 2
// uint8 CANCEL = 3

	int ID;
	ID = req.ID;

	if(findPath(pathToFollow, listOfPath, ID))
	{
		res.accepted = true;
	}
	else
		res.accepted = false;

	return true;
}

/*-----  End of Others Functions  ------*/

/*=================================
=            Main Save            =
=================================*/

/*
	// Pour envoyer des goals au robotino_lcal_move_server
	RobotinoLocalMoveClient rlmc;

	// if( rlmc.checkServer() )
	// {
	// 	rlmc.sendGoal( goal );
	// 	rlmc.spin();
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
	// 	executeurDeChemin::command::Response accepted = true;
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
					float goal_x	= pathToFollow.poses[i].pose.position.x;
					float goal_y	= pathToFollow.poses[i].pose.position.y;
					float goal_phi	= tf::getYaw(pathToFollow.poses[i].pose.orientation);
				
					float dx		= goal_x - current_x;
					float dy		= goal_y - current_y;
					float dphi		= atan(dx/dy) - current_phi;
					
					float tolerance		= 0.01;		//au cm près
					float tolerancePhi 	= PI/90;	//à 2° près
				
					//On dirige l'avant du robot vers le point à atteindre
					robotino_local_move::LocalMoveGoal rotation;
					
					rotation.move_x 			= 0.0;
					rotation.move_y 			= 0.0;
					rotation.rotation 			= dphi * 180 / PI;		//en °
					rotation.ignore_rotation 	= false;
					
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
			
			dernier = i;		//on mémorise la dernière pose à chaque fois
								//au cas où le manager fait pause
		}
	
		//Dernière pose refaite par sécurité
		goal_x		= pathToFollow.poses[dernier].pose.position.x;
		goal_y		= pathToFollow.poses[dernier].pose.position.y;
		goal_phi	= tf::getYaw(pathToFollow.poses[dernier].pose.orientation);
				
		dx			= goal_x - current_x;
		dy			= goal_y - current_y;
		dphi		= goal_phi - current_phi;
				
		goal.move_x = dx;
		goal.move_y = dy;
		goal.rotation = dphi;
		goal.ignore_rotation = false;
		
		bool poseOK = (	client.getState() == succes &&
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

