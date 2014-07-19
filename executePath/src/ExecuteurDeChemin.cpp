#include "executePath/ExecuteurDeChemin.h"

bool findPath(rbqt_pathfinder::AstarPath &pathFound, std::list<rbqt_pathfinder::AstarPath> listOfPath, int ID)
{
	std::list<rbqt_pathfinder::AstarPath>::iterator iter;

	for(iter = listOfPath.begin(); iter != listOfPath.end(); iter++)
	{
		if(iter->id == ID)
		{	
			pathFound = *iter;
    		return true;
		}
	}

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
