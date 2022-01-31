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

#include "Config.h"

//====================================================================================================
//Constructor:
Config::Config(){
	windowWidth = DEFAULT_WINDOW_WIDTH;
	windowHeight = DEFAULT_WINDOW_HEIGHT;
	initialAsteroidCount = 0;
	asteroidSpawnInterval = 0;
	ShipTurnRate = 0;
	shipTurnRateModifier = 1;
	shipThrust = 0;
	shipThrustModifier = 1;
}


//====================================================================================================
//Mutators:
void Config::setConfig(std::string& fileName){

	std::ifstream inputCheck;
	inputCheck.open(fileName);

	if(inputCheck.is_open()) //Check if config file exists before starting.
		processConfig(fileName);

	else
		outputNewConfig(fileName); //Create a new config file if none exists.

	inputCheck.close();

	//Set config settings.
	if(windowWidth == 0 || windowWidth > WINDOW_WIDTH_UPPER_LIMIT || windowWidth < WINDOW_WIDTH_LOWER_LIMIT)
		windowWidth = DEFAULT_WINDOW_WIDTH;

	if(windowHeight == 0 || windowHeight > WINDOW_HEIGHT_UPPER_LIMIT || windowHeight < WINDOW_HEIGHT_LOWER_LIMIT)
		windowHeight = DEFAULT_WINDOW_HEIGHT;

	if(initialAsteroidCount == 0 || initialAsteroidCount > INITIAL_ASTEROID_COUNT_UPPER_LIMIT || initialAsteroidCount < INITIAL_ASTEROID_COUNT_LOWER_LIMIT)
		initialAsteroidCount = DEFAULT_INITIAL_ASTEROID_COUNT;

	if(asteroidSpawnInterval == 0 || asteroidSpawnInterval > ASTEROID_SPAWN_INTERVAL_UPPER_LIMIT || asteroidSpawnInterval < ASTEROID_SPAWN_INTERVAL_LOWER_LIMIT)
		asteroidSpawnInterval = DEFAULT_ASTEROID_SPAWN_INTERVAL;
	else
		asteroidSpawnInterval = asteroidSpawnInterval * FRAMERATE;

	if(shipThrust == 0 || shipThrust > SHIP_THRUST_UPPER_LIMIT || shipThrust < SHIP_THRUST_LOWER_LIMIT)
		shipThrust = DEFAULT_SHIP_THRUST;
	else
		shipThrust = static_cast<float>(shipThrust * FRAMERATE * 0.5); //Convert meters per second to pixels per frame.

	if(shipThrust == DEFAULT_SHIP_THRUST)
		shipThrust *= shipThrustModifier; //If still default multiply by modifier.

	if(ShipTurnRate == 0 || ShipTurnRate > SHIP_TURN_RATE_UPPER_LIMIT || ShipTurnRate < SHIP_TURN_RATE_LOWER_LIMIT)
		ShipTurnRate = DEFAULT_SHIP_TURN_RATE;
	else
		ShipTurnRate = ShipTurnRate / 120; //Convert degrees per second to degrees per frame.

	if(ShipTurnRate == DEFAULT_SHIP_TURN_RATE)
		ShipTurnRate *= shipTurnRateModifier; //If still default multiply by modifier.
}

//====================================================================================================
//Accessors:

//==================================================
//Function: getWindowHeight
//Description: Returns the window height.
//
//Return value:
//	The window height.
//==================================================
unsigned int Config::getWindowHeight(){
	return windowHeight;
}

//==================================================
//Function: getWindowWidth
//Description: Returns the window width.
//
//Return value:
//	The window width.
//==================================================
unsigned int Config::getWindowWidth(){
	return windowWidth;
}

//==================================================
//Function: getInitialAsteroidCount
//Description: Returns the intitial asteroid number.
//
//Return value:
//	The initial asteroid count.
//==================================================
int Config::getInitialAsteroidCount(){
	return initialAsteroidCount;
}

//==================================================
//Function: getAsteroidSpawnInterval
//Description: Returns the asteroid spawn interval.
//
//Return value:
//	The asteroid spawn interval.
//==================================================
int Config::getAsteroidSpawnInterval(){
	return asteroidSpawnInterval;
}

//==================================================
//Function: getShipTurnRate
//Description: Returns the ship turn rate setting.
//
//Return value:
//	The ship turn rate setting.
//==================================================
float Config::getShipTurnRate(){
	return ShipTurnRate;
}

//==================================================
//Function: getShipTurnRateMod
//Description: Returns the ship turn rate modifier.
//
//Return value:
//	The ship turn rate modifier.
//==================================================
float Config::getShipTurnRateMod(){
	return shipTurnRateModifier;
}

//==================================================
//Function: getShipThrust
//Description: Returns the ship thrust setting.
//
//Return value:
//	The ship thrust setting.
//==================================================
float Config::getShipThrust(){
	return shipThrust;
}

//==================================================
//Function: getShipThrustMod
//Description: Returns the ship thrust modifier.
//
//Return value:
//	The ship thrust modifier.
//==================================================
float Config::getShipThrustMod(){
	return shipThrustModifier;
}

//====================================================================================================
//Others:

//==================================================
//Function: processConfig
//Description: 
//
//Return value:
//	
//==================================================
void Config::processConfig(std::string& fileName){

	std::ifstream inputData;

	//open the file. 
	inputData.open(fileName);

	while(inputData.good()){
		readChar = inputData.get();

		//Check if line is to be ignored.
		if(readChar == '/')
			getline(inputData, readLine); //Dump line.

		//Check if line is window data.
		else if(readChar == 'w')
			inputData >> windowWidth >> windowHeight;

		//Check if line is asteroid data.
		else if(readChar == 'a'){
			readChar = inputData.get();
			if(readChar == 'i') //Check if asteroid data is for initial count.
				inputData >> initialAsteroidCount;
			else if(readChar == 's') //Check if asteroid data is for spawn interval.
				inputData >> asteroidSpawnInterval;
			else
				getline(inputData, readLine); //Dump line.
		}

		//Check if line is ship data.
		else if(readChar == 't'){
			readChar = inputData.get();
			if(readChar == 'h'){ //Check if ship data is for thrust.
				readChar = inputData.get();
				if(readChar == 'a') //Check if thrust data is an absolute value.
					inputData >> shipThrust;
				else if(readChar == '%') //Check if thrust data is a percent modifier.
					inputData >> shipThrustModifier;
				else
					getline(inputData, readLine); //Dump line.
			}
			else if(readChar == 'r'){ //Check if ship data is for turn rate.
				readChar = inputData.get();
				if(readChar == 'a') //Check if turn rate data is an absolute value.
					inputData >> ShipTurnRate;
				else if(readChar == '%') //Check if turn rate data is a percent modifier.
					inputData >> shipThrustModifier;
				else
					getline(inputData, readLine); //Dump line.
			}
		}
		else
			getline(inputData, readLine); //Dump line.
	}
	//close the file.
	inputData.close();
}

//==================================================
//Function: outputNewConfig
//Description: 
//
//Return value:
//	
//==================================================
void Config::outputNewConfig(std::string& fileName){

	std::ofstream outputData;

	//open the file 
	outputData.open(fileName); 

	//Write config file.
	outputData << "/Hello! This file has been created to assist you in custom tuning your brand new Space Warthog." << std::endl;
	outputData << "/Please follow the instructions carefully. As you may have noticed notes are preceded by a '/' and are not processed." << std::endl;
	outputData << "/The following is a key to the possible options. A template has been created below with the default values." << std::endl;
	outputData << "/The letters at the beginning of a line determine what it changes please follow the format carefully!" << std::endl;
	outputData << "/Some possible tweaks are percentage changes of the default values instead of absolute values." << std::endl;
	outputData << "/If both an absolue and a percent value are entered, the percent will be ignored." << std::endl;
	outputData << std::endl;
	outputData << "/w	Changes the width and height of the display window. Please follow it with two number, a width and a height with a space between." << std::endl;
	outputData << "/ai	Changes the number of asteroids that spawn at the beginning of the battle. Please follow it with a single number." << std::endl;
	outputData << "/as	Changes the rate at which asteroids enter the battlefield. Please follow it with a delay time in seconds. (Decimal values are accepted!)" << std::endl;
	outputData << "/tha	Changes the thrust of the Warthog. Please follow it with a thrust value in meters per second^2. (Decimal values are accepted!)" << std::endl;
	outputData << "/th%	Changes the thrust of the Warthog with a multiplier. Please follow it with a decimal multiplier. (e.g. 0.5 for half thrust) Note: Default thrust is ~3.5 m/s^2." << std::endl;
	outputData << "/tra	Changes the turn rate of the Warthog. Please follow it with an angular velocity value in degrees per second." << std::endl;
	outputData << "/tr%	Changes the turn rate of the Warthog with a multiplier. Please follow it with a decimal multiplier. (e.g. 0.5 for half turn speed.) Note: Default turn speed is 180 degrees per second" << std::endl;
	outputData << std::endl;
	outputData << "/Template: (Please remove the '/' to activate a line.)" << std::endl;
	outputData << "/w 800 600" << std::endl;
	outputData << "/ai 5" << std::endl;
	outputData << "/as 3" << std::endl;
	outputData << "/tha 3.5" << std::endl;
	outputData << "/th% 1" << std::endl;
	outputData << "/tra 180" << std::endl;
	outputData << "/tr& 1" << std::endl;

	//close the file 
	outputData.close(); 

}


//====================================================================================================
//Friends: