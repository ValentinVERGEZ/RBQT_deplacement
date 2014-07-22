#ifndef _HEADER_OBJET_
#define _HEADER_OBJET_

#ifdef GRAPHIC
    //SFML
    #include <SFML/Graphics.hpp>
#endif

enum typeObjet{MACHINE,ROBOTINO,DELIVERY,RECYCLING};

class Objet
{
public:
	Objet(typeObjet type, float x, float y);
	Objet(typeObjet type, float x, float y,int phi);
	~Objet();
	int setPosition(float x, float y);
	int setPosition(float x, float y, int phi);
	int setType(typeObjet type);
	float getX() const;
	float getY() const;
	int getPhi() const;
#ifdef GRAPHIC
	int constuctShape();
	int draw(sf::RenderWindow &w);
#endif

private:
	// Position de l'objet
	float _x;
	float _y;
	int _phi;	

	// Type
	typeObjet _type;

	// Graphique
	#ifdef GRAPHIC
public:
		sf::Shape *_shape;
	#endif
};

#endif	// _HEADER_OBJET_