#ifndef _SERVER_STATIC_UTILS_HEADER_
#define _SERVER_STATIC_UTILS_HEADER_

#include <iostream>

#ifdef GRAPHIC
#include <SFML/Graphics.hpp>
#endif // GRAPHIC

#include "ros/ros.h"
#include "tf/transform_datatypes.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/PoseStamped.h"

#include "rbqt_pathfinder/GeneratePath.h"
#include "rbqt_pathfinder/AstarPath.h"
#include "rbqt_pathfinder/AstarState.h"

#include <boost/thread/thread.hpp>
#include <vector>

#define OFFSET_GRID 0.56 

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

typedef struct GridPoint
{
    GridPoint(int a, int b)
    {
        x = a;
        y = b;
    }
    
    int x;
    int y;
} GridPoint;

typedef std::vector<GridPoint> GridPath;

typedef std::vector<GridPath> tabGridPath;

extern geometry_msgs::PoseStamped origin;
extern std::vector<rbqt_pathfinder::AstarPath> &AstarTab;
extern PathOrders pathReq;
extern rbqt_pathfinder::AstarPath  pathFound;
extern rbqt_pathfinder::AstarState pathfinderState;
extern int lastIdReceived;
extern std::vector<GridPath> &StaticTab;

void defineOrigin(geometry_msgs::PoseStamped &origin, float xorigin, float yorigin);

geometry_msgs::PoseStamped calculPoint (int xgrille,
                                        int ygrille,
                                        geometry_msgs::PoseStamped origin,
                                        float OffsetGrid);

void inverserChemin(GridPath &Chemin);

void initGridPath(std::vector<GridPath> &tab);

void initAstarPath (std::vector<rbqt_pathfinder::AstarPath> &AstarTab,
                    tabGridPath &StaticTab);

void getPathFromStartPoint (rbqt_pathfinder::AstarPath tab,
                            float xdepart, 
                            float ydepart,
                            std::vector<rbqt_pathfinder::AstarPath> &tabResult);

void getPathFromEndPoint   (std::vector<rbqt_pathfinder::AstarPath> tabResult,
                            float xarrivee,
                            float yarrivee,
                            rbqt_pathfinder::AstarPath &Path);

bool generatePath_callback (rbqt_pathfinder::GeneratePath::Request  &req,
         					rbqt_pathfinder::GeneratePath::Response &res);

void computeAStar_thread_function();

#endif // _SERVER_STATIC_UTILS_HEADER_