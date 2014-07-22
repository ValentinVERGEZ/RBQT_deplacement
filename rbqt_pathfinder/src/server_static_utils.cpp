#include "rbqt_pathfinder/server_static_utils.h"

geometry_msgs::PoseStamped &origin;

std::vector<rbqt_pathfinder::AstarPath> &AstarTab;

void defineOrigin(geometry_msgs::PoseStamped &origin, float xorigin, float yorigin)
{
    origin.pose.position.x = xorigin;
    origin.pose.position.y = yorigin;
}

geometry_msgs::PoseStamped calculPoint (int xgrille,
                                        int ygrille,
                                        geometry_msgs::PoseStamped origin,
                                        float offset)
{
    geometry_msgs::PoseStamped P;
    
    P.pose.position.x = (float)xgrille*offset + origin.pose.position.x;
    P.pose.position.y = (float)ygrille*offset + origin.pose.position.y;
    
    return P;
}

void inverserChemin(GridPath &Chemin)
{
    for (int i = 0; i < Chemin.size(); i++)
    {
        Chemin[i].x = -Chemin[i].x;
    }
}

void initGridPath(std::vector<GridPath> &StaticTab)
{
    GridPath Chemin1;
    
    Chemin1.push_back(GridPoint(5, 0));
    Chemin1.push_back(GridPoint(4, 0));
    Chemin1.push_back(GridPoint(3, 0));
    Chemin1.push_back(GridPoint(2, 1));
    Chemin1.push_back(GridPoint(2, 2));
    Chemin1.push_back(GridPoint(2, 3));
    Chemin1.push_back(GridPoint(1, 3));
    
    GridPath Chemin2;
    
    Chemin2.push_back(GridPoint(1, 3));
    
    GridPath Chemin3;
    
    Chemin3.push_back(GridPoint(1, 3));
    Chemin3.push_back(GridPoint(2, 3));
    Chemin3.push_back(GridPoint(3, 3));
    
    GridPath Chemin4;
    
    Chemin4.push_back(GridPoint(3, 3));

    GridPath Chemin5;
    
    Chemin5.push_back(GridPoint(3, 3));
    Chemin5.push_back(GridPoint(2, 3));
    Chemin5.push_back(GridPoint(2, 4));
    Chemin5.push_back(GridPoint(2, 5));
    Chemin5.push_back(GridPoint(3, 5));
    
    GridPath Chemin6;
    
    Chemin6.push_back(GridPoint(7, 0));
    Chemin6.push_back(GridPoint(6, 1));
    Chemin6.push_back(GridPoint(6, 2));
    Chemin6.push_back(GridPoint(6, 3));
    Chemin6.push_back(GridPoint(7, 3));
    
    GridPath Chemin7;
    
    Chemin7.push_back(GridPoint(7, 3));
    Chemin7.push_back(GridPoint(6, 3));
    Chemin7.push_back(GridPoint(5, 3));
    
    GridPath Chemin8;
    
    Chemin8.push_back(GridPoint(5, 3));
    Chemin8.push_back(GridPoint(5, 4));
    Chemin8.push_back(GridPoint(5, 5));
    
    GridPath Chemin9;
    
    Chemin9.push_back(GridPoint(7, 3));
    Chemin9.push_back(GridPoint(6, 3));
    Chemin9.push_back(GridPoint(5, 3));
    
    GridPath Chemin10;
    
    Chemin10.push_back(GridPoint(9, 0));
    Chemin10.push_back(GridPoint(8, 1));
    Chemin10.push_back(GridPoint(8, 2));
    Chemin10.push_back(GridPoint(8, 3));
    Chemin10.push_back(GridPoint(8, 4));
    Chemin10.push_back(GridPoint(8, 5));
    Chemin10.push_back(GridPoint(8, 6));
    Chemin10.push_back(GridPoint(9, 7));
    
    GridPath Chemin11;
    
    Chemin11.push_back(GridPoint(9, 7));
    Chemin11.push_back(GridPoint(8, 7));
    Chemin11.push_back(GridPoint(7, 7));
    
    GridPath Chemin12;
    
    Chemin12.push_back(GridPoint(7, 7));
    Chemin12.push_back(GridPoint(6, 7));
    Chemin12.push_back(GridPoint(5, 7));
    
    StaticTab.push_back(Chemin1);
    inverserChemin(Chemin1);
    StaticTab.push_back(Chemin1);
    
    StaticTab.push_back(Chemin2);
    inverserChemin(Chemin2);
    StaticTab.push_back(Chemin2);
    
    StaticTab.push_back(Chemin3);
    inverserChemin(Chemin3);
    StaticTab.push_back(Chemin3);
    
    StaticTab.push_back(Chemin4);
    inverserChemin(Chemin4);
    StaticTab.push_back(Chemin4);

    StaticTab.push_back(Chemin5);
    inverserChemin(Chemin5);
    StaticTab.push_back(Chemin5);
    
    StaticTab.push_back(Chemin6);
    inverserChemin(Chemin6);
    StaticTab.push_back(Chemin6);
    
    StaticTab.push_back(Chemin7);
    inverserChemin(Chemin7);
    StaticTab.push_back(Chemin7);
    
    StaticTab.push_back(Chemin8);
    inverserChemin(Chemin8);
    StaticTab.push_back(Chemin8);
    
    StaticTab.push_back(Chemin9);
    inverserChemin(Chemin9);
    StaticTab.push_back(Chemin9);
    
    StaticTab.push_back(Chemin10);
    inverserChemin(Chemin10);
    StaticTab.push_back(Chemin10);
    
    StaticTab.push_back(Chemin11);
    inverserChemin(Chemin11);
    StaticTab.push_back(Chemin11);
    
    StaticTab.push_back(Chemin12);
    inverserChemin(Chemin12);
    StaticTab.push_back(Chemin12);
}

void initAstarPath (std::vector<rbqt_pathfinder::AstarPath> &AstarTab,
                    std::vector<GridPath> &StaticTab)
{      
    for (int i = 0; i < StaticTab.size(); i++)
    {
        rbqt_pathfinder::AstarPath Path;
    
        for (int j = 0; j < StaticTab[i].size(); j++)
        {
            geometry_msgs::PoseStamped P = calculPoint( StaticTab[i][j].x,
                                                        StaticTab[i][j].y,
                                                        origin,
                                                        (float)OFFSET_GRID);
            //type de la forme(int&, int&, geometry_msgs::PoseStamped&, double)
            //pas cohérent avec le prototype du .h(float, float, geometry_msgs::PoseStamped, float)

            Path.path.poses.push_back(P);
        }
        
        AstarTab.push_back(Path);
    }
}

void getPathFromStartPoint (std::vector<rbqt_pathfinder::AstarPath> tab,
                            float xdepart, 
                            float ydepart,
                            std::vector<rbqt_pathfinder::AstarPath> &tabResult)
{
    for (int i = 0; i < tab.size(); i++)
    {
        if (tab[i].path.poses.begin()->pose.position.x == xdepart &&
            tab[i].path.poses.begin()->pose.position.y == ydepart)
        {
            tabResult.push_back(tab[i]);
        }
    }
}

void getPathFromEndPoint   (std::vector<rbqt_pathfinder::AstarPath> tabResult,
                            float xarrivee,
                            float yarrivee,
                            rbqt_pathfinder::AstarPath &pathFound)
{
    for (int i = 0; i < tabResult.size(); i++)
    {
        if (tabResult[i].path.poses.end()->pose.position.x == xarrivee &&
            tabResult[i].path.poses.end()->pose.position.y == yarrivee)
        {
            pathFound = tabResult[i];
        }
    }
}

void computeAStar_thread_function()
{
    boost::posix_time::milliseconds     sleep_time(10);
    int lastId = -1;
    PathOrders actualOrders;

    while(1)
    {
        if(lastId != pathReq.id)
        {
            std::vector<rbqt_pathfinder::AstarPath> tabResult;

            pathReq.processing = true;
            pathfinderState.state = pathfinderState.EN_COURS;

            lastId = pathReq.id;

            actualOrders = pathReq;

            pathFound.id = actualOrders.id;
            pathFound.path.poses.erase(pathFound.path.poses.begin(),pathFound.path.poses.end());
            
            getPathFromStartPoint(AstarTab,
                                  actualOrders.startPose.x,
                                  actualOrders.startPose.y,
                                  tabResult);

            getPathFromEndPoint(tabResult,
                                actualOrders.goalPose.x,
                                actualOrders.goalPose.y,
                                pathFound);

            pathfinderState.id = actualOrders.id;

            if (pathFound.path.poses.size() <= 0)
            {
                pathfinderState.state = pathfinderState.SUCCES;
            }
            else
            {
                pathfinderState.state = pathfinderState.ECHEC;
            }

            pathfinderState.id = pathFound.id;

            pathReq.processing = false;
        }

        boost::this_thread::sleep(sleep_time);
    }
}