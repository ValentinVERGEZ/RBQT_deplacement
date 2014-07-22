#ifndef _SERVER_HEADER_
#define _SERVER_HEADER_

/*==========  Includes  ==========*/
//StdLib
    #include <iostream>

    // #define GRAPHIC
    #ifdef GRAPHIC
    //SFML
    #include <SFML/Graphics.hpp>
    #endif // GRAPHIC

    // Perso
    #include "rbqt_pathfinder/Map.hpp"
    #include "rbqt_pathfinder/Objet.hpp"
    #include "rbqt_pathfinder/Point.hpp"

    #include "rbqt_pathfinder/GeneratePath.h"
    #include "rbqt_pathfinder/AstarPath.h"
    #include "rbqt_pathfinder/AstarState.h"

    #include "ros/ros.h"
    #include "tf/transform_datatypes.h"
    #include "nav_msgs/Path.h"

    #include <boost/thread/thread.hpp>


/*==========  Types  ==========*/
typedef struct{
    int id;
    struct
    {
        float x;
        float y;      
        float yaw;  
    } goalPose;
    struct
    {
        float x;
        float y;        
    } startPose;
    char processing;
} PathOrders;

/*==========  Declarations  ==========*/
bool generatePath_callback(rbqt_pathfinder::GeneratePath::Request  &req,
         rbqt_pathfinder::GeneratePath::Response &res);
void computeAStar_thread_function();

#endif // _SERVER_HEADER_
