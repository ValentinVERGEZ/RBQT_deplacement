#include "rbqt_pathfinder/Objet.hpp"


	Objet::Objet(typeObjet type, float x, float y)
	{
		setType(type);
		setPosition(x, y);
		_phi = 0;

	#ifdef GRAPHIC
		constuctShape();
	#endif
	}

	Objet::Objet(typeObjet type, float x, float y, int phi)
	{
		setType(type);
		setPosition(x, y, phi);

	#ifdef GRAPHIC
		constuctShape();
	#endif
	}

	Objet::~Objet()
	{
	}

	int Objet::setPosition(float x, float y)
	{
		_x = x;
		_y = y;

		return 0;
	}

	int Objet::setPosition(float x, float y, int phi)
	{	
		setPosition(x, y);
		_phi = (phi%360);
        if (_phi > 180)
        {
            _phi = _phi-360;
        }
        else 	if(_phi <= -180)
		        {
		            _phi = _phi+360;
		        }

		return 0;
	}

	int Objet::setType(typeObjet type)
	{	
		_type = type;

		return 0;
	}

	float Objet::getX() const
	{
		return _x;
	}

	float Objet::getY() const
	{
		return _y;
	}

	int Objet::getPhi() const
	{
		return _phi;
	}


#ifdef GRAPHIC
	int Objet::constuctShape()
	{
		switch(_type)
		{
			case MACHINE:
				_shape = new sf::RectangleShape(sf::Vector2f(50, 50));
		        _shape->setFillColor(sf::Color::White);
		        _shape->setOutlineThickness(-2);
		        _shape->setOutlineColor(sf::Color::Black);
		        _shape->setPosition((int)(562.5-_x*100)-25, 38+_y*100-25);
		        _shape->setRotation(0);
			break;

			case RECYCLING:
				_shape = new sf::RectangleShape(sf::Vector2f(50, 50));
		        _shape->setFillColor(sf::Color::White);
		        _shape->setOutlineThickness(-2);
		        _shape->setOutlineColor(sf::Color::Green);
		        _shape->setPosition((int)(562.5-_x*100)-25, 38+_y*100-25);
		        _shape->setRotation(0);
			break;

			case DELIVERY:
				_shape = new sf::RectangleShape(sf::Vector2f(40, 20));
		        _shape->setFillColor(sf::Color::Green);
		        _shape->setOutlineThickness(-2);
		        _shape->setOutlineColor(sf::Color::Black);
		        _shape->setPosition((int)(562.5-_x*100)-25, 38+_y*100-25);
		        _shape->setRotation(0);
			break;

			case ROBOTINO:
				_shape = new sf::CircleShape(37.5/2);
		        _shape->setFillColor(sf::Color::Blue);
		        _shape->setOutlineThickness(-2);
		        _shape->setOutlineColor(sf::Color::Black);
			break;

			default:
				_shape = new sf::CircleShape(0);
			break;
		}

		return 0;
	}

	int Objet::draw(sf::RenderWindow &w)
	{
		w.draw(*_shape);
		return 0;
	}

#endif