//====================================================================================================
//Header: GunSmoke (class) 
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class for puffs of smoke that come out of the ship when it fires.
//
//Revision date: Mar 06 2014
//====================================================================================================

#include "GunSmoke.h"

//====================================================================================================
//Constructors:
GunSmoke::GunSmoke(Config inputSettings) : SpaceObject(inputSettings){
	
}

GunSmoke::GunSmoke(Config settings, FloatVector velocity, FloatVector location, float angle) : SpaceObject(settings){

	state = SMOKE_ALIVE;
	setLocation(calculateRelativePosition(location, angle, 16).x, calculateRelativePosition(location, angle, 16).y);
	setVelocity(velocity.x, velocity.y);

	//Set angle.
	float angleMod = 0;
	angleMod = static_cast<float>(((rand() % 450) / 10.0));
	if(rand() % 2)
		angleMod *= -1;
	setAngle(angle + angleMod);

	applyThrust(SMOKE_THRUST);
}

//Destructor:
GunSmoke::~GunSmoke(){
}

//====================================================================================================
//Mutators:

//==================================================
//Function: decay
//Description: Sets FragState to FRAG_DEAD.
//
//==================================================
void GunSmoke::decay(){
	state = SMOKE_DEAD;
}


//====================================================================================================
//Accessors:


//==================================================
//Other:

//==================================================
//Function: drawGunSmoke
//Description: Draws the puffs of smoke that come out
//	of the ship when the gun fires.
//
//Argument list:
//	window(I): The window to be drawn on.
//==================================================
void GunSmoke::drawGunSmoke(sf::RenderWindow& window, sf::Texture& gunSmoke){

	sf::Sprite smokeSprite;
	smokeSprite.setTexture(gunSmoke);
	smokeSprite.setOrigin(5,5);
	smokeSprite.setPosition(getLocation().x, getLocation().y);

	window.draw(smokeSprite);
}