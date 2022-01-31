//====================================================================================================
//Header: Asteroid (class) 
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class for asteroid objects.
//
//Revision date: Feb 14 2014
//====================================================================================================

#ifndef RAND_DESIG_ASTEROID_gy071FjSpN
#define RAND_DESIG_ASTEROID_gy071FjSpN

#include "SpaceObject.h"
#include "DustCloud.h"

enum AsteroidState {AS_LARGE, AS_MEDIUM, AS_SMALL, AS_DESTROYED, AS_GONE};

class Asteroid : public SpaceObject {
private:
	AsteroidState state;
	int asteroidSides;
	int asteroidHitPoints;
	int explosionTimer;
	DustCloud* clouds[DUST_ARRAY_SIZE];

public:
	//Constructor:
	Asteroid(Config settings, AsteroidState inputState = AS_LARGE, bool subAsteroid = false, float parentLocationX = 0, float parentLocationY = 0);

	//Destructor:
	~Asteroid();

	//==================================================
	//Mutators:
	void damageAsteroid(int damage);
	void destroyAsteroid();

	//==================================================
	//Accessors:
	int getHitPoints();
	AsteroidState getState();

	//==================================================
	//Others:
	void draw(sf::RenderWindow& window, sf::Texture& dustCloud);
	void drawAlive(sf::RenderWindow& window);
	void drawDestroyed(sf::RenderWindow& window, sf::Texture& dustCloud);
};

#endif