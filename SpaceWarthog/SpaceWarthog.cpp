//====================================================================================================
//Project: Space Warthog: Asteroid Hunter
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: An asteroids-like based on the A-10 Warthog.
//
//Revision date: Mar 08 2014
//====================================================================================================

#include "game.h"
#include "Config.h"

int main(){

	std::string fileName = "SpaceWarthog.txt";

	//Load settings.
	Config settings;
	settings.setConfig(fileName);

	//Game loop.
	game(settings);

}