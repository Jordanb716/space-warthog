//====================================================================================================
//Header: Bullet (class) 
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class for storing bullet data.
//
//Revision date: Mar 06 2014
//====================================================================================================

#ifndef RAND_DESIG_BULLET_UQPwOCnyph
#define RAND_DESIG_BULLET_UQPwOCnyph

#include "SpaceObject.h"

class Bullet : public SpaceObject {
private:

public:
	//Constructors:
	Bullet(Config settings);
	Bullet(Config settings, const FloatVector velocity, const FloatVector location, const float angle);

	//Deconstructor
	~Bullet();

	//==================================================
	//Mutators:

	//==================================================
	//Accessors:

	//==================================================
	//Others:
	void drawBullet(sf::RenderWindow& window);
};

#endif