/*==========  Includes  ==========*/

#include "executePath/ExecuteurDeChemin.h"

/*==========  Global Variables  ==========*/
	// Paths
	std::list<rbqt_pathfinder::AstarPath> listOfPath;
	rbqt_pathfinder::AstarPath pathToFollow;

	// Message
	executePath::EdCState EdCState_msg;

	// Odométrie
	float current_x		= 0.0;
	float current_y		= 0.0;
	float current_phi = 0.0;

	// Infos
	uint8_t	lastState = executePath::EdCState::LIBRE;

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
	EdCState_msg.ID = -1;

	// Thread
	boost::thread executePath(&executePath_thread);

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
	switch(req.type)
	{
		case executePath::command::Request::EXECUTE_PATH :
			int ID;
			ID = req.ID;

			// On execute un nouveau chemin que si on est libre (LIBRE, FINISHED et BAD_ID)
			if(EdCState_msg.state == executePath::EdCState::LIBRE
				|| EdCState_msg.state == executePath::EdCState::BAD_ID
				|| EdCState_msg.state == executePath::EdCState::FINISHED)
			{
				if(findPath(pathToFollow, listOfPath, ID))
				{
					res.accepted = true;
					lastState = EdCState_msg.state;
					EdCState_msg.state = executePath::EdCState::IN_PROGRESS;
					EdCState_msg.ID = ID;
				}
				else
				{
					res.accepted = false;
					lastState = EdCState_msg.state;
					EdCState_msg.state = executePath::EdCState::BAD_ID;											
				}
			}
			else
			{
				res.accepted = false;
			}
			break;

		case executePath::command::Request::PAUSE :
			// On met PAUSE que quand un chemin s'execute (PROBLEM, OBSTACLE, IN_PROGRESS)
			if(EdCState_msg.state == executePath::EdCState::IN_PROGRESS
				|| EdCState_msg.state == executePath::EdCState::OBSTACLE
				|| EdCState_msg.state == executePath::EdCState::PROBLEM)
			{
				res.accepted = true;
				lastState = EdCState_msg.state;
				EdCState_msg.state = executePath::EdCState::PAUSED;		
			}
			else
			{
				res.accepted = false;
			}
			break;

		case executePath::command::Request::RESUME :
			// On RESUME uniquement quand on est en pause
			if(EdCState_msg.state == executePath::EdCState::PAUSED)
			{
				res.accepted = true;
				EdCState_msg.state = lastState;	
				lastState = executePath::EdCState::PAUSED;
			}
			else
			{
				res.accepted = false;
			}
			break;

		case executePath::command::Request::CANCEL :
			// On annulle que quand un chemin s'execute ou est en pause (PROBLEM, OBSTACLE, IN_PROGRESS, PAUSED)
			if(EdCState_msg.state == executePath::EdCState::IN_PROGRESS
				|| EdCState_msg.state == executePath::EdCState::OBSTACLE
				|| EdCState_msg.state == executePath::EdCState::PROBLEM
				|| EdCState_msg.state == executePath::EdCState::PAUSED)
			{
				res.accepted = true;
				lastState = EdCState_msg.state;
				EdCState_msg.state = executePath::EdCState::LIBRE;		
			}
			else
			{
				res.accepted = false;
			}
			break;

		default:
			res.accepted = false;
			break;
	}

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


// Called once when the goal completes
void doneCb(const actionlib_msgs::GoalStatus& state,
            const robotino_local_move::LocalMoveResult& result)
{
  ROS_INFO("Finished in state [%s]", state.toString().c_str());
  ROS_INFO("Answer: %i", result.goal_reached);
}

// Called once when the goal becomes active
void activeCb()
{
  ROS_INFO("Goal just went active");
}

// Called every time feedback is received for the goal
void feedbackCb(const robotino_local_move::LocalMoveActionFeedback& feedback)
{
  ROS_INFO("Got Feedback of length %lu", feedback.sequence.size());
}

// Thread d'execution du chemin
void executePath_thread()
{

}

/*-----  End of Others Functions  ------*/