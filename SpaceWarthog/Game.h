//====================================================================================================
//Project: Game (main)
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: The game loop and main functions.
//
//Scale: 0.5 meters per pixel
//
//Revision date: Mar 08 2014
//====================================================================================================

#ifndef RAND_DESIG_GAME_Wpg1JHXKEd
#define RAND_DESIG_GAME_Wpg1JHXKEd

#include <SFML\Graphics.hpp>
#include "Config.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Constants.h"
#include "GunSmoke.h"

//Function prototypes
int game(Config settings);
void cycleDamagedAsteroids(Config settings, Asteroid* rocky[]);
void createSubAsteroid(Config settings, Asteroid* rocky[], int parentNumber);

#endif