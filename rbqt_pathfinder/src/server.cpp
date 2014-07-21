/*==========  Includes  ==========*/
#include "rbqt_pathfinder/server.hpp"


/*==========  Global variables  ==========*/
PathOrders pathReq = {-1,{0,0,0.0},{0,0},false};
rbqt_pathfinder::AstarPath pathFound;
rbqt_pathfinder::AstarState pathfinderState;
int lastIdReceived = -1;

/*==========  Main  ==========*/
int main(int argc, char **argv)
{
    ros::init(argc, argv, "server");
    ros::NodeHandle n;


    pathfinderState.state = pathfinderState.LIBRE;
    pathfinderState.id = lastIdReceived;
    pathFound.id = lastIdReceived;

    ros::Publisher path_pub = n.advertise<rbqt_pathfinder::AstarPath>("pathFound", 1000);
    ros::Publisher state_pub = n.advertise<rbqt_pathfinder::AstarState>("pathfinderState", 1000);
    ros::ServiceServer service = n.advertiseService("generatePath", generatePath_callback);
    ROS_INFO("Ready to compute A Star pathfinding.");

    boost::thread computeAStar_thread(&computeAStar_thread_function);

    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        path_pub.publish(pathFound);
        state_pub.publish(pathfinderState);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}

/*==========  Other functions  ==========*/
bool generatePath_callback(rbqt_pathfinder::GeneratePath::Request  &req,
         rbqt_pathfinder::GeneratePath::Response &res)
{
    ROS_INFO("GeneratePath request - ID : %d", req.id);
    if(!req.utilisePositionOdometry){
        ROS_INFO("Pose Depart (Utilisation du parametre) : \nX: %f | Y : %f | Theta : %f",req.Depart.position.x,req.Depart.position.y,tf::getYaw(req.Depart.orientation));
    }
    else
    {
        ROS_INFO("Pose Depart (Utilisation de l'odometrie): \nX: %f | Y : %f | Theta : %f",0.0,0.0,0.0);
    }
    ROS_INFO("Pose Arrivee : \nX: %f | Y : %f | Theta : %f",req.Arrivee.position.x,req.Arrivee.position.y,tf::getYaw(req.Arrivee.orientation));

    if(pathReq.processing == true || req.id == lastIdReceived){
        res.requeteAcceptee = false;
    }
    else{
        res.requeteAcceptee = true;
        lastIdReceived = req.id;

        pathReq.id = req.id;
        pathReq.goalPose.x = req.Arrivee.position.x;
        pathReq.goalPose.y = req.Arrivee.position.y;
        pathReq.goalPose.yaw = tf::getYaw(req.Arrivee.orientation);
        if(!req.utilisePositionOdometry)
        {
            pathReq.startPose.x = req.Depart.position.x;
            pathReq.startPose.y = req.Depart.position.y;
        }
        else
        {
            // TODO : USE ODOMETRY
            pathReq.startPose.x = 0;
            pathReq.startPose.y = 0;
        }
    }

  return true;
}


void computeAStar_thread_function()
{
    boost::posix_time::milliseconds     sleep_time(10);
    int lastId = -1;
    PathOrders actualOrders;

    Map mapRobocup;
    Point *startPoint,*endPoint;
    std::vector<Point*> chemin;

    while(1)
    {
        if(lastId != pathReq.id)
        {
            pathReq.processing = true;
            pathfinderState.state = pathfinderState.EN_COURS;

            lastId = pathReq.id;

            actualOrders = pathReq;

            mapRobocup.getNearestPoint(pathReq.goalPose.x,pathReq.goalPose.y,endPoint);
            mapRobocup.getNearestPoint(pathReq.startPose.x,pathReq.startPose.y,startPoint);

            ROS_INFO("computeAStar with : Start - x %d | y %d  /  End - x %d | y %d",startPoint->getX(),startPoint->getY(),endPoint->getX(),endPoint->getY());

            pathFound.id = actualOrders.id;
            pathFound.path.poses.erase(pathFound.path.poses.begin(),pathFound.path.poses.end());
            mapRobocup.computeAStar(chemin, startPoint, endPoint);

            pathfinderState.id = actualOrders.id;
            if(chemin.front() == startPoint && chemin.back() == endPoint)
            {
                std::size_t i;

                for(i=0;i<chemin.size()-1;++i) {
                    geometry_msgs::PoseStamped point;
                    point.pose.position.x = chemin[i]->getX();
                    point.pose.position.y = chemin[i]->getY();
                    pathFound.path.poses.push_back(point);
                }
                geometry_msgs::PoseStamped pointFinal;
                pointFinal.pose.position.x = chemin[i]->getX();
                pointFinal.pose.position.y = chemin[i]->getY();
                pointFinal.pose.orientation = tf::createQuaternionMsgFromYaw(actualOrders.goalPose.yaw);
                pathFound.path.poses.push_back(pointFinal);

                pathfinderState.state = pathfinderState.SUCCES;
            }
            else
                pathfinderState.state = pathfinderState.ECHEC;

            ROS_INFO("%p == %p && %p == %p",chemin.front(), startPoint, chemin.back(), endPoint);

            pathReq.processing = false;
        }

        boost::this_thread::sleep(sleep_time);
    }
}











// int main()
// {

//     //Environment
//     Map mapRobocup;
//     Point *startPoint,*endPoint;
//     std::vector<Point*> chemin;

//     // Algo
//     while (1)
//     {
//         unsigned int sLi,sCol,eLi,eCol;
//         std::cout << "Veuillez indiquer les lignes et colonnes pour le point start et le point end : " << std::endl;
//         std::cin >> sLi;
//         std::cin >> sCol;
//         std::cin >> eLi;
//         std::cin >> eCol;
//         mapRobocup.getPointAt(sLi,sCol,startPoint);
//         mapRobocup.getPointAt(eLi,eCol,endPoint);
//         mapRobocup.computeAStar(chemin,startPoint,endPoint);

//         std::cout << "Taille du chemin trouvé : " << chemin.size() << std::endl;

//         std::cout << "Depart : " << startPoint->getLigne() << "," << startPoint->getColonne() << std::endl;
//         for (unsigned int i = 0; i < chemin.size(); ++i)
//         {
//             std::cout << "\tPoint : " << chemin[i]->getLigne() << "," << chemin[i]->getColonne() << " f :" << chemin[i]->getF()  << " g :" << chemin[i]->getG()  << " h :" << chemin[i]->getH() << std::endl;
//         }
//         std::cout << "Arrivee : " << endPoint->getLigne() << "," << endPoint->getColonne() << std::endl;        
//     }


//     return 0;
// }

