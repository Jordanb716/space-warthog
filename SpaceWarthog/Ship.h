//====================================================================================================
//Header: Ship (class) 
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class for storing ship data.
//
//Revision date: Mar 06 2014
//====================================================================================================

#ifndef RAND_DESIG_SHIP_2U1DeTXMpE
#define RAND_DESIG_SHIP_2U1DeTXMpE

#include "SpaceObject.h"
#include "ShipFragment.h"
#include "Bullet.h"
#include "GunSmoke.h"
#include "Asteroid.h"

enum ShipState { SS_ALIVE, SS_EXPLODING, SS_GONE };

class Ship : public SpaceObject {
private:
	ShipState state;
	bool engineIsFiring;
	bool gunIsFiring;
	bool isTurningLeft;
	bool isTurningRight;
	bool fragmentDataSet;
	int explosionTimer;
	int gunTimer;
	ShipFragment* debris[SHIP_FRAG_NUMBER];

public:
	//Constructor:
	Ship(Config settings);

	//Destructor:
	~Ship();

	//==================================================
	//Mutators:
	void explode();
	void setEngineFiring(bool engineState);
	void setGunFiring(bool gunState);
	void setTurningLeft(bool leftTurnState);
	void setTurningRight(bool rightTurnState);
	void detectFragmentCollision(Asteroid* asteroidArray[]);

	//==================================================
	//Accessors:
	bool checkEngineFiring();
	bool checkGunFiring();
	bool checkTurningLeft();
	bool checkTurningRight();
	bool checkIsExploding();
	ShipState getState();
	ShipFragment getFrag();

	//==================================================
	//Others:
	void rotateLeft();
	void rotateRight();
	void fireGun(Bullet* bulletArray[], int& bulletArrayPosition, GunSmoke* smokeArray[], int& smokeArrayPosition);
	void draw(sf::RenderWindow& window);
	void drawAliveShip(sf::RenderWindow& window);
	void drawExplodingShip(sf::RenderWindow& window);
};

#endif