//====================================================================================================
//Header: Config (class)
//Author: Jordan Bergmann
//Environment: Visual Studio 2013 (C++)
//
//Description: A class to store settings for the game and functions to manipulate them.
//	Key:
//	w	Window height, window width.
//	ai	Initial asteroid count.
//	as	Asteroid spawn interval in seconds.
//	tha	Ship thrust in pixels per second.
//	th%	Percent modifier for default ship thrust.
//	tra	Ship turn rate in degrees per second.
//	tr%	Percent modifier for default ship turn rate.
//
//	Percent modifiers cannot be used with absolute modifiers, percent will be ignored.
//
//Revision date: Mar 09 2014
//====================================================================================================

#ifndef RAND_DESIG_CONFIG_sKPc4xGwlP
#define RAND_DESIG_CONFIG_sKPc4xGwlP

#include <string>
#include <fstream>
#include "Constants.h"
#include "Vector.h"

class Config {
private:
	unsigned int windowWidth;	//Width of game window.
	unsigned int windowHeight;	//Height of game window.
	int initialAsteroidCount;	//Number of asteroids at beginning of game.
	int asteroidSpawnInterval;	//Time between asteroid spawns.
	float shipThrust;			//Thrust in pixels per frame.
	float shipThrustModifier;	//A modifier for the default thrust setting.
	float ShipTurnRate;			//Turn rate in degrees per second.
	float shipTurnRateModifier;	//A multiplier for the default turn rate.
	char readChar;
	std::string readLine;

public:
	//Constructor:
	Config();

	//==================================================
	//Mutators:
	void setConfig(std::string& fileName);

	//==================================================
	//Accessors:
	unsigned int getWindowHeight();
	unsigned int getWindowWidth();
	int getInitialAsteroidCount();
	int getAsteroidSpawnInterval();
	float getShipThrust();
	float getShipThrustMod();
	float getShipTurnRate();
	float getShipTurnRateMod();

	//==================================================
	//Others:
	void processConfig(std::string& fileName);
	void outputNewConfig(std::string& fileName);

	//==================================================
	//Friends:

};

#endif