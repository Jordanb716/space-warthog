//====================================================================================================
//Header: SpaceObject (class) 
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class with general functions for objects in space.
//
//Revision date: Mar 08 2014
//====================================================================================================

#ifndef RAND_DESIG_SHIPFRAG_hg6J6cYkVl
#define RAND_DESIG_SHIPFRAG_hg6J6cYkVl

#include "SpaceObject.h"
#include "Config.h"

enum FragState { FRAG_ALIVE, FRAG_DEAD };

class ShipFragment : public SpaceObject{
private:
	FragState state;
	FloatVector sizeMod;

public:
	//Constructor:
	ShipFragment(Config settings);

	//Destructor:
	~ShipFragment();

	//==================================================
	//Mutators:
	void setFragData(const FloatVector velocity, const FloatVector location);
	void decay();

	//==================================================
	//Accessors:
	FloatVector getSizeMod();
	FragState getState();

	//==================================================
	//Other:
	void drawDebris(sf::RenderWindow& window);
};

#endif