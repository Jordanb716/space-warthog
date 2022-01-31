//====================================================================================================
//Project: ShipFragment (class)
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class for storing ship fragment data.
//
//Revision date: Mar 08 2014
//====================================================================================================

#include "ShipFragment.h"

//====================================================================================================
//Constructor:
ShipFragment::ShipFragment(Config inputSettings) : SpaceObject(inputSettings){
	state = FRAG_ALIVE;
	setRadius(10);
	setDecayTimer(rand() % SHIP_FRAG_MAX_LIVE_TIME);
	sizeMod.x = static_cast<float>(rand() % SHIP_FRAG_MAX_SIZE_MOD);
	sizeMod.y = static_cast<float>(rand() % SHIP_FRAG_MAX_SIZE_MOD);
}

//Destructor:
ShipFragment::~ShipFragment(){
}

//====================================================================================================
//Mutators:

//==================================================
//Function: setFragData
//Description: Sets the location, velocity, and rotational velocity
//	based on the exploding ship plus random values.
//
//Argument list:
//	ship(I): The ship to get base data from.
//==================================================
void ShipFragment::setFragData(const FloatVector velocity, const FloatVector location){

	//Set location
	setLocation(location.x, location.y);

	//==================================================
	//Set velocity:

	//Set angle.
	setAngle(static_cast<float>(rand() % 359));

	//Apply thrust once to set velocity.
	applyThrust((rand() % (SHIP_FRAG_VELOCITY_MOD + 1) + 5) * SHIP_FRAG_VELOCITY_MULTIPLIER);

	//Add ships velocity.
	cngVelocity(velocity.x, velocity.y);

	//==================================================
	//Set rotational velocity:
	int fragRotDirection = 1;

	if(rand() % 2)
		fragRotDirection = -1;

	setRotationalVelocity(((static_cast<float>((rand() % SHIP_FRAG_MAX_ROTATIONAL_VELOCITY) + 2) / 10)) * fragRotDirection);
}

//==================================================
//Function: decay
//Description: Sets FragState to FRAG_DEAD.
//
//==================================================
void ShipFragment::decay(){
	state = FRAG_DEAD;
}


//====================================================================================================
//Accessors:

//==================================================
//Function: getSizeMod
//Description: Gets the size modifier.
//
//==================================================
FloatVector ShipFragment::getSizeMod(){
	return sizeMod;
}

//==================================================
//Function: getState
//Description: Gets FragState.
//
//Return (FragState):
//	FRAG_ALIVE: Fragment exists and should be drawn.
//	FRAG_DEAD: Fragment has decayed and should not be drawn.
//==================================================
FragState ShipFragment::getState(){
	return state;
}


//==================================================
//Other:

//==================================================
//Function: drawDebris
//Description: Draws the ship explosion and wreckage to the screen.
//
//Argument list:
//	window(I): The window to be drawn on.
//==================================================
void ShipFragment::drawDebris(sf::RenderWindow& window){

	//Update properties.
	updateLocation(6);
	updateAngle();

	//Define Fragments
	sf::ConvexShape frag;

	frag.setPointCount(3);
	frag.setPoint(0, sf::Vector2f(0, 0));
	frag.setPoint(1, sf::Vector2f(0, 2 + sizeMod.y));
	frag.setPoint(2, sf::Vector2f(2 + sizeMod.x, 0));
	frag.setOrigin(2, 2);

	//Color fragments.
	frag.setFillColor(sf::Color(184, 196, 196));

	//Set part location and rotation.
	frag.setPosition(getLocation().x, getLocation().y);
	frag.setRotation(getAngle());

	//==================================================
	//Draw fragments:
	window.draw(frag);
}