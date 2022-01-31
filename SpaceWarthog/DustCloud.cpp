//====================================================================================================
//Header: DustCloud (class) 
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class for clouds of dust created when asteroids are destroyed.
//
//Revision date: Mar 06 2014
//====================================================================================================

#include "DustCloud.h"

//====================================================================================================
//Constructors:
DustCloud::DustCloud(Config inputSettings) : SpaceObject(inputSettings){

}

DustCloud::DustCloud(Config settings, FloatVector velocity, FloatVector location) : SpaceObject(settings){

	state = DUST_ALIVE;
	setLocation(location.x, location.y);
	setVelocity(velocity.x, velocity.y);
	setAngle(static_cast<float>(rand() % 359));
	applyThrust(DUST_THRUST);
}

//Destructor:
DustCloud::~DustCloud(){
}

//====================================================================================================
//Mutators:

//==================================================
//Function: decay
//Description: Sets FragState to FRAG_DEAD.
//
//==================================================
void DustCloud::decay(){
	state = DUST_DEAD;
}


//====================================================================================================
//Accessors:


//==================================================
//Other:

//==================================================
//Function: drawDustCloud
//Description: Draws the puffs of smoke that come out
//	of the ship when the gun fires.
//
//Argument list:
//	window(I): The window to be drawn on.
//==================================================
void DustCloud::drawDustCloud(sf::RenderWindow& window, sf::Texture& dustCloud, int time){

	//Update properties.
	updateLocation(50);

	sf::Sprite cloud;
	cloud.setTexture(dustCloud);
	cloud.setOrigin(50,50);
	cloud.setPosition(getLocation().x, getLocation().y);
	cloud.setScale(static_cast<float>(1.5 * time / ASTEROID_EXPLOSION_TIME + 0.5), static_cast<float>(1.5 * time / ASTEROID_EXPLOSION_TIME + 0.5));

	window.draw(cloud);
}