//====================================================================================================
//Header: SpaceObject (class) 
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class with general functions for objects in space.
//
//Revision date: Mar 08 2014
//====================================================================================================

#ifndef RAND_DESIG_SPACEOBJ_ko5WE4bgeK
#define RAND_DESIG_SPACEOBJ_ko5WE4bgeK

#include <SFML\Graphics.hpp>
#include <cmath>
#include "Config.h"
#include "Constants.h"
#include "Vector.h"

class SpaceObject {
private:
	int decayTimer;
	IntVector locationBoundaries;	//Maximum allowable values for location.
	FloatVector objectLocation;		//Current location (x,y).
	FloatVector objectVelocity;		//Current velocity (in pixels/frame).
	float objectRotVelocity;		//Current rotational velocity (in degrees per frame).
	float objectAngle;				//Angle ship is facing, in degrees.
	float objectRadius;				//Average radius of ship (for collision detection).

public:

	Config settings;

	//Constructor:
	SpaceObject(Config Settings);

	//==================================================
	//Mutators:
	void setMaxLocation(int newXBoundary, int newYBoundary);
	void setLocation(float newX, float newY);
	void setVelocity(float newVelocityX, float newVelocityY);
	void setRotationalVelocity(float newRotVelocity);
	void setAngle(float newAngle);
	void setRadius(float newRadius);
	void cngVelocity(float deltaVx, float deltaVy);
	void cngAngle(float deltaA);
	void cngRadius(float deltaR);
	void setDecayTimer(int time);
	void incrementDecayTimer();
	void decrementDecayTimer();

	//==================================================
	//Accessors:
	float getRadius();
	FloatVector getLocation();
	FloatVector getVelocity();
	FloatVector getRotVelocity();
	float getAngle();
	int getDecayTime();

	//==================================================
	//Others:
	void applyThrust(double thrust);
	void rotateLeft(float turnSpeed);
	void rotateRight(float turnSpeed);
	void updateLocation(float givenRadius = 0);
	void updateAngle();

	//==================================================
	//Friends:
	friend bool detectCollision(SpaceObject object1, SpaceObject object2);
	friend float calculateAngle(SpaceObject object1, SpaceObject object2);
	friend double calculateVelocity(SpaceObject object);
	friend Vector calculateDeltaV(SpaceObject object1, SpaceObject object2);
	friend FloatVector calculateRelativePosition(FloatVector origin, float angle, float distance);
};

#endif