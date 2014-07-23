#include "executePath/ExecuteurDeChemin.h"

bool findPath(rbqt_pathfinder::AstarPath &pathFound, std::list<rbqt_pathfinder::AstarPath> listOfPath, int ID)
{
	std::list<rbqt_pathfinder::AstarPath>::iterator iter;

	ROS_INFO("Fonction findPath() : ");
	for(iter = listOfPath.begin(); iter != listOfPath.end(); iter++)
	{
		ROS_INFO("ID : %d",iter->id);
		if(iter->id == ID)
		{	
			pathFound = *iter;
			ROS_INFO("TROUVE : ID : %d",iter->id);
    		return true;
		}
	}
	
	ROS_INFO("NON TROUVE : ID : %d",iter->id);

	return false;
}

bool checkServer(actionlib::SimpleActionClient<robotino_local_move::LocalMoveAction> &client)
{
	for( int i = 0; i < 5; ++i)
	{
		// ros::spinOnce();
		if( client.waitForServer( ros::Duration( 1.0 ) ) )
		{
			ROS_INFO( "Connected to the local move server" );
			return true;
		}
		else
		{
			ROS_INFO( "Waiting for local move server" );
		}
	}

	ROS_ERROR( "local move server not running" );
	return false;
}

// void send(robotino_local_move::RobotinoLocalMoveClient client, robotino_local_move::LocalMoveGoal goal)
// {
// 	if (client.checkServer())
// 	{
// 		client.sendGoal(goal);
// 		client.spin();
// 	}
// }
