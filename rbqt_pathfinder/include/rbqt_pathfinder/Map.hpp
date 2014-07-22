#ifndef _HEADER_MAP_
#define _HEADER_MAP_

#include "Point.hpp"
#include "Objet.hpp"
#include <set>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cfloat>

#ifdef GRAPHIC
    //SFML
    #include <SFML/Graphics.hpp>
#endif

enum typeHeuristic{MANHATTAN,EUCLIDEAN,Chebyshev};

class Map
{
public:
	Map();
	~Map();

	// AStar
	void setAllowDiagonal(bool allowDiagonal);
	void setCrossCorner(bool crossCorner);
	void setPoidsHeuristic(signed int poids);
	float heuristic(Point const& pointDepart, Point const& pointDistant);
	float heuristicManhattan(Point const& pointDepart, Point const& pointDistant);
	float heuristicEuclidean(Point const& pointDepart, Point const& pointDistant);
	float heuristicChebyshev(Point const& pointDepart, Point const& pointDistant);
	void setHeuristicFunction(typeHeuristic heuristicFonction);
	bool isFreeAt(signed int li, signed int col);
	signed int getVoisins(std::vector<Point*> &voisins, Point *oirigin);
	signed int computeAStar(std::vector<Point*> &chemin, Point *startPoint, Point *endPoint);
	signed int getPointAt(signed int ligne, signed int colonne, Point*& point) const;
	signed int getNearestPoint(float x, float y, Point*& point) const;

#ifdef GRAPHIC
	int drawObjects(sf::RenderWindow &w);
#endif

private:
	// Machines
	const static int nbProductionMachine = 24;
	const static int nbDeliveryMachine = 6;
	const static int nbRecyclingMachine = 2;
	Objet *_production_machine[nbProductionMachine];
	Objet *_delivery_machine[nbDeliveryMachine];
	Objet *_recycling_machine[nbRecyclingMachine];

	// Points
	const static int nbPointsLignes = 9;
	const static int nbPointsColonnes = 19;
	Point *_pointsPassage[nbPointsLignes][nbPointsColonnes];

	// AStar	
	bool _allowDiagonal;
	bool _crossCorner;
	signed int _poidsHeuristic;
	typeHeuristic _heuristicFonction;
};

class CompareF
{
public:
    bool operator()(Point* const& a, Point* const& b) const
    {
    	float valFa = a->getF()*1000000+((a->getLigne()*100)%100)+(a->getColonne()%100);
    	float valFb = b->getF()*1000000+((b->getLigne()*100)%100)+(b->getColonne()%100);
        return (valFa < valFb);
    }
};

#endif	// _HEADER_MAP_