//====================================================================================================
//Header: GunSmoke (class) 
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class for puffs of smoke that come out of the ship when it fires.
//
//Revision date: Mar 06 2014
//====================================================================================================

#ifndef RAND_DESIG_SMOKE_nUiHgaL44k
#define RAND_DESIG_SMOKE_nUiHgaL44k

#include "SpaceObject.h"

enum SmokeState { SMOKE_ALIVE, SMOKE_DEAD };

class GunSmoke : public SpaceObject {
private:
	SmokeState state;

public:
	//Constructors:
	GunSmoke(Config settings);
	GunSmoke(Config settings, FloatVector velocity, FloatVector location, float angle);

	//Deconstructor
	~GunSmoke();

	//==================================================
	//Mutators:
	void decay();

	//==================================================
	//Accessors:

	//==================================================
	//Others:
	void drawGunSmoke(sf::RenderWindow& window, sf::Texture& gunSmoke);
};

#endif