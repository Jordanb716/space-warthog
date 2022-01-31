//====================================================================================================
//Header: Ship (class) 
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class for storing ship data.
//
//Revision date: Feb 23 2014
//====================================================================================================

#ifndef RAND_DESIG_CONSTANTS_qvGOJARjrR
#define RAND_DESIG_CONSTANTS_qvGOJARjrR

//General.
const double PI = 3.14159265358979;
const int FRAMERATE = 120;

//Defaults.
const unsigned int DEFAULT_WINDOW_WIDTH = 800;
const unsigned int DEFAULT_WINDOW_HEIGHT = 600;

const int DEFAULT_INITIAL_ASTEROID_COUNT = 5;
const int DEFAULT_ASTEROID_SPAWN_INTERVAL = ( 3/*seconds*/ * FRAMERATE);

const int HAWG_THRUST = 80640; //Newtons (real A-10 thrust)
const int HAWG_MASS = 23000; //Kilograms
const float DEFAULT_SHIP_THRUST = static_cast<float>(((HAWG_THRUST/HAWG_MASS)*0.5)/FRAMERATE); //Force/Mass*(Meters per pixel)/framerate
const float DEFAULT_SHIP_TURN_RATE = 1.5; //Degrees per frame

//Config limits
const int FRAMERATE_UPPER_LIMIT = 240;
const int FRAMERATE_LOWER_LIMIT = 30;

const int WINDOW_WIDTH_UPPER_LIMIT = 2560;
const int WINDOW_WIDTH_LOWER_LIMIT = 800;
const int WINDOW_HEIGHT_UPPER_LIMIT = 1440;
const int WINDOW_HEIGHT_LOWER_LIMIT = 600;

const int ASTEROID_SPAWN_INTERVAL_UPPER_LIMIT = ( 10/*seconds*/ * FRAMERATE);
const int ASTEROID_SPAWN_INTERVAL_LOWER_LIMIT = static_cast<int>( 0.1/*seconds*/ * FRAMERATE);
const int INITIAL_ASTEROID_COUNT_UPPER_LIMIT = 20;
const int INITIAL_ASTEROID_COUNT_LOWER_LIMIT = 0;

const float SHIP_THRUST_UPPER_LIMIT = static_cast<float>( 1/*seconds*/ * FRAMERATE);
const float SHIP_THRUST_LOWER_LIMIT = static_cast<float>( 0.001/*seconds*/ * FRAMERATE);
const float SHIP_TURN_RATE_UPPER_LIMIT = static_cast<float>(5);
const float SHIP_TURN_RATE_LOWER_LIMIT = static_cast<float>(0.1);

//Warthog.
const float SHIP_RADIUS = 16;
const int SHIP_FLASH_TIME = (static_cast<int>( 0.5/*seconds*/ * FRAMERATE));
const int SHIP_EXPLOSION_TIME = ( 10/*Seconds*/ * FRAMERATE); //Time explosion happens for.
const int SHIP_GUN_DELAY_TIME = (FRAMERATE / 25/*bullets fired per second*/);

//Ship Fragment.
const int SHIP_FRAG_NUMBER = 400; //The number of fragments created on ship explosion.
const int SHIP_FRAG_VELOCITY_MOD = 35; //This value / 100 is the max modifier for fragment velocity
const float SHIP_FRAG_VELOCITY_MULTIPLIER = static_cast<float>(0.01); //Calculated random velocity int is multiplied by this to get actual velocity in pixels per frame.
const int SHIP_FRAG_MAX_ROTATIONAL_VELOCITY = 20; //This value / 10 is actual max rotational velocity.
const int SHIP_FRAG_MAX_LIVE_TIME = ( 6/*seconds*/ * FRAMERATE); //Maximum time a fragment can live for.
const int SHIP_FRAG_MAX_SIZE_MOD = 8; //Maximum number of pixels that can be added to the size of any one side of a fragment.

//Asteroid.
const int ASTEROID_MAX_NUM = 25; //Maximum number of asteroids that can exist at one time.
const float ASTEROID_BASE_RADIUS = 50; //Pixels
const int ASTEROID_VELOCITY_RANGE = ((6)/*upper bound*/ - (3)/*lower bound*/);
const float ASTEROID_VELOCITY_MULTIPLIER = static_cast<float>(0.1); //Calculated random velocity int is multiplied by this to get actual velocity in pixels per frame.
const int ASTEROID_MAX_ROTATIONAL_VELOCITY = 15; //This value / 10 is actual max rotational velocity.
const int ASTEROID_HIT_POINTS_LARGE = 8; //The number of times a large asteroid can be hit by bullets before it it destroyed;
const int ASTEROID_HIT_POINTS_MEDIUM = 4; //The number of times a medium asteroid can be hit by bullets before it it destroyed;
const int ASTEROID_HIT_POINTS_SMALL = 2; //The number of times a small asteroid can be hit by bullets before it it destroyed;
const int ASTEROID_CREATION_NUM_MEDIUM = 3; //The number of medium asteroids created when a large asteroid is destroyed.
const int ASTEROID_CREATION_NUM_SMALL = 4; //The number of small asteroids created when a medium asteroid is destroyed.
const int ASTEROID_EXPLOSION_TIME = static_cast<int>( 0.5/*Seconds*/ * FRAMERATE); //Time explosion happens for.

//Bullet.
const int BULLET_MAX_NUM = 60;
const float BULLET_THRUST = 3;

//Effects
const int SMOKE_MAX_NUM = 10;
const float SMOKE_THRUST = static_cast<float>(0.2);
const int SMOKE_LIVE_TIME = static_cast<int>( 0.3/*Seconds*/ * FRAMERATE); //Time smoke lasts for.

const int DUST_ARRAY_SIZE = 3; //Number of clouds created for each asteroid destroyed.
const float DUST_THRUST = static_cast<float>(1); //Thrust given when cloud is created.

#endif