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

	// Bumper
	bool bumperState = false;

	// Infos
	uint8_t	lastState = executePath::EdCState::LIBRE;

	// Service
	Request servReq;
	unsigned int actualProcessedPose = 0;
	bool firstRotationAlreadyDone = false;
	bool goalAlreadySent = false;

/*============================
=            Main            =
============================*/


int main(int argc, char** argv)
{

	//Initialisation du noeud ROS
	ros::init(argc, argv, "executeur_de_chemin");
	
	ros::NodeHandle n;
	
	//Souscription aux topics utiles
	ros::Subscriber sub_odo = n.subscribe("/odom", 1000, odomCallback);
	ros::Subscriber sub_bump = n.subscribe("/bumper", 1000, bumperCallback);
	ros::Subscriber sub_pathFound = n.subscribe("/pathFound", 1000, pathfinderCallback);
	
	//Création d'un topic d'état EdCState
	ros::Publisher EdCState_pub = n.advertise<executePath::EdCState>("EdCState", 1000);
	
	//Création d'un service "command"
	servReq.type = Request::NOTHING;
	servReq.ID = -1;
	ros::ServiceServer service = n.advertiseService("command", &serviceCallback);

	//Init message
	EdCState_msg.state = executePath::EdCState::LIBRE;
	EdCState_msg.ID = -1;

	// Thread
	boost::thread executePath(&executePath_thread);

	ros::Rate loop_rate (100);
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

void bumperCallback(std_msgs::Bool bumper)
{
	bumperState = bumper.data;
}

void pathfinderCallback(rbqt_pathfinder::AstarPath pathFound)
{
	// ROS_INFO("pathfinderCallback");

	if(listOfPath.size() == 0 || listOfPath.back().id != pathFound.id)
	{		
		listOfPath.push_back(pathFound);

		ROS_INFO("New path - id %d",listOfPath.back().id);
	
		if(listOfPath.size() > NB_MAX_PATH_SAVED)
	   	{
	   		listOfPath.pop_front();
	   	}
	}
}

bool serviceCallback(executePath::command::Request  &req,
        executePath::command::Response &res)
{
	ROS_INFO("Req reçue - ID : %d | Type : %d",req.ID,req.type);
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
					servReq = req;
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
				servReq = req;
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
				servReq = req;
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
				servReq = req;
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

	return true;
}


// Called once when the goal completes
void doneCb(const actionlib::SimpleClientGoalState& state,
            const robotino_local_move::LocalMoveResultConstPtr result)
{
  // ROS_INFO("Finished in state [%s]", state.toString().c_str());
  // ROS_INFO("Answer: %i", result.goal_reached);

	if(!firstRotationAlreadyDone)
	{
		firstRotationAlreadyDone = true;
	}
	else
	{
		if(actualProcessedPose == pathToFollow.path.poses.size())
		{
			actualProcessedPose = 0;
			servReq.type == Request::NOTHING;
			firstRotationAlreadyDone = false;
			goalAlreadySent = false;
		}
		else
		{
			actualProcessedPose++;
			firstRotationAlreadyDone = false;
			goalAlreadySent = false;
		}
	}
}

// Called once when the goal becomes active
void activeCb()
{
  ROS_INFO("Goal just went active");
  goalAlreadySent = true;
}

// Called every time feedback is received for the goal
void feedbackCb(const robotino_local_move::LocalMoveFeedbackConstPtr feedback)
{
  // ROS_INFO("Got Feedback of length %lu", feedback.sequence.size());
}

// Thread d'execution du chemin
void executePath_thread()
{
// Environement
    boost::posix_time::milliseconds     sleep_time(10);

	// Client - actionlib	
    actionlib::SimpleActionClient<robotino_local_move::LocalMoveAction> localMoveClient("local_move", true);

    robotino_local_move::LocalMoveGoal actualGoal;

// Algo

	while(1)
	{		

		switch(servReq.type)
		{
			case Request::EXECUTE_PATH:

			if(!checkServer(localMoveClient))
			{
				EdCState_msg.state = executePath::EdCState::PROBLEM;
	        	boost::this_thread::sleep(sleep_time);
				continue;
			}
			
			if(goalAlreadySent)
				continue;

			// Construct goal
				// Dernier point - Rotation + Avance avec Rotation (fixee)
				if(actualProcessedPose == pathToFollow.path.poses.size())
				{
					// Avance
					if(firstRotationAlreadyDone)
					{		
						actualGoal.move_x = calculateForwardDisplacementNeeded(current_x, current_y, pathToFollow.path.poses[actualProcessedPose].pose.position.x,pathToFollow.path.poses[actualProcessedPose].pose.position.y);
						actualGoal.move_y = 0.0;
						actualGoal.rotation = tf::getYaw(pathToFollow.path.poses[actualProcessedPose].pose.orientation);

					actualGoal.ignore_rotation = false;	
					}
					// Rotation
					else
					{	
						actualGoal.move_x = 0.0;
						actualGoal.move_y = 0.0;

						actualGoal.rotation = calculateRotationNeeded(current_x, current_y, pathToFollow.path.poses[actualProcessedPose].pose.position.x,pathToFollow.path.poses[actualProcessedPose].pose.position.y);

						actualGoal.ignore_rotation = false;
					}
				}
				// Autre point - Rotation + Avance
				else
				{
					// Avance
					if(firstRotationAlreadyDone)
					{		
						actualGoal.move_x = calculateForwardDisplacementNeeded(current_x, current_y, pathToFollow.path.poses[actualProcessedPose].pose.position.x,pathToFollow.path.poses[actualProcessedPose].pose.position.y);
						actualGoal.move_y = 0.0;
						actualGoal.rotation = 0.0;

					actualGoal.ignore_rotation = true;	
					}
					// Rotation
					else
					{	
						actualGoal.move_x = 0.0;
						actualGoal.move_y = 0.0;

						actualGoal.rotation = calculateRotationNeeded(current_x, current_y, pathToFollow.path.poses[actualProcessedPose].pose.position.x,pathToFollow.path.poses[actualProcessedPose].pose.position.y);

						actualGoal.ignore_rotation = false;
					}
				}
				localMoveClient.sendGoal(actualGoal, &doneCb, &activeCb, &feedbackCb);
				break;

			case Request::PAUSE:
				break;

			case Request::RESUME:
				break;
				
			case Request::CANCEL:
			goalAlreadySent = false;
				break;

			case Request::NOTHING:
			default:
				break;
		}

        boost::this_thread::sleep(sleep_time);
	}	
}

float calculateRotationNeeded(float startX, float startY, float endX, float endY)
{
	float dy = (endY - startY);
	float dx = (endX - startX);

	float phi = atan(abs(dy/dx));

	if(dx >= 0)
	{
		if(dy < 0)
			phi *= -1;
	}
	else
	{
		if(dy < 0)
			phi = -M_PI + phi;
		else
			phi = M_PI - phi;
	}
	return phi;
}

float calculateForwardDisplacementNeeded(float startX, float startY, float endX, float endY)
{
	float dy = abs(startY - endY);
	float dx = abs(startX - endX);

	return sqrt(dx*dx+dy*dy) ;
}


/*-----  End of Others Functions  ------*/