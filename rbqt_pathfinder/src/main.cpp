/* Includes */
    //StdLib
    #include <iostream>
    #include <cmath>

    //SFML
    #include <SFML/Graphics.hpp>

    // Perso
    #include "main.hpp"
    #include "Map.hpp"
    #include "Objet.hpp"
    #include "Point.hpp"

/* Global variables and constants*/

    // Thread periods
    const unsigned int JOY_THD_SLEEP(50);

/* Main */
int main()
{
    //Environment
    Map mapRobocup;
    Point *startPoint,*endPoint;
    std::vector<Point*> chemin;

    #ifdef GRAPHIC
        // Fenêtre de dessin
        sf::RenderWindow windowMap(sf::VideoMode(1125, 600), "Robocup Area");

    // Algo
    while (windowMap.isOpen())
    {
        // Gestion de tous les events depuis la dernière itération
        sf::Event event;
        while (windowMap.pollEvent(event))
        {
            // Fermeture de la fenêtre si demandée
            if (event.type == sf::Event::Closed)
                windowMap.close();
        }

        // Draw window
        windowMap.clear(sf::Color::White);
        mapRobocup.drawObjects(windowMap);
        windowMap.display();

        unsigned int sLi,sCol,eLi,eCol;
        ROS_INFO("Veuillez indiquer les lignes et colonnes pour le point start et le point end : ");
        std::cin >> sLi;
        std::cin >> sCol;
        std::cin >> eLi;
        std::cin >> eCol;
        mapRobocup.getPointAt(sLi,sCol,startPoint);
        mapRobocup.getPointAt(eLi,eCol,endPoint);
        mapRobocup.computeAStar(chemin,startPoint,endPoint);

        ROS_INFO("Taille du chemin trouvé : %d", chemin.size());

        ROS_INFO("Depart : [%d , %d]", startPoint->getLigne(), startPoint->getColonne());
        for (unsigned int i = 0; i < chemin.size(); ++i)
        {
            ROS_INFO("\tPoint : [%d , %d]", chemin[i]->getLigne(), chemin[i]->getColonne());
            ROS_INFO("f : %f", chemin[i]->getF());
            ROS_INFO("g : %f", chemin[i]->getG());
            ROS_INFO(" h :" << chemin[i]->getH());
        }
        ROS_INFO("Arrivee : [%d , %d]", endPoint->getLigne(), endPoint->getColonne());        
    }

    #endif

    return 0;
}