#ifndef _EXECUTEUR_DE_CHEMIN_HEADER_
#define _EXECUTEUR_DE_CHEMIN_HEADER_ 
/*==========  Includes  ==========*/

#include "ros/ros.h"

// #include "robotino_local_move/LocalMoveGoal.h"
// #include "RobotinoLocalMoveClient.h"

#include "rbqt_pathfinder/AstarPath.h"
#include "executePath/EdCState.h"
#include "executePath/command.h"

#include <actionlib/client/simple_action_client.h>
#include <tf/transform_datatypes.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/Odometry.h>
#include <cmath>
#include <list>

//nettoyage à faire dans les #include

/*==========  DEFINES  ==========*/

#ifndef M_PI
    #define M_PI 3.14159265359
#endif
#define NB_MAX_PATH_SAVED 10
#define  sucess actionlib::SimpleClientGoalState::SUCCEEDED

/*==========  DECLARATIONS - main.cpp  ==========*/

void odomCallback(nav_msgs::Odometry odom);
void pathfinderCallback(const rbqt_pathfinder::AstarPath pathFound);
bool serviceCallback(executePath::command::Request &req, executePath::command::Response &res);

/*==========  DECLARATIONS - ExecuteruDeChemin.cpp  ==========*/

bool findPath(rbqt_pathfinder::AstarPath &pathFound, std::list<rbqt_pathfinder::AstarPath> listOfPath, int ID);
// void send(robotino_local_move::RobotinoLocalMoveClient client, robotino_local_move::LocalMoveGoal goal);

#endif  // _EXECUTEUR_DE_CHEMIN_HEADER_