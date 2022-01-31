//====================================================================================================
//Header: DustCloud (class) 
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class for clouds of dust created when asteroids are destroyed.
//
//Revision date: Mar 06 2014
//====================================================================================================

#ifndef RAND_DESIG_DUST_jB7Tqupty0
#define RAND_DESIG_DUST_jB7Tqupty0

#include "SpaceObject.h"

enum DustState { DUST_ALIVE, DUST_DEAD };

class DustCloud : public SpaceObject {
private:
	DustState state;

public:
	//Constructors:
	DustCloud(Config settings);
	DustCloud(Config settings, FloatVector velocity, FloatVector location);

	//Deconstructor
	~DustCloud();

	//==================================================
	//Mutators:
	void decay();

	//==================================================
	//Accessors:

	//==================================================
	//Others:
	void drawDustCloud(sf::RenderWindow& window, sf::Texture& dustCloud, int time);
};

#endif