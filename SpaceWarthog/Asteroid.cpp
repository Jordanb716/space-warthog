//====================================================================================================
//Header: Asteroid (class) 
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class for asteroid objects.
//
//Revision date: Mar 09 2014
//====================================================================================================

#include "Asteroid.h"

//====================================================================================================
//Constructor:
Asteroid::Asteroid(Config inputSettings, AsteroidState inputState, bool subAsteroid, float parentLocationX, float parentLocationY) : SpaceObject(inputSettings){

	//==================================================
	//Set misc.
	state = inputState;
	asteroidSides = 8;
	explosionTimer = 0;

	if(state == AS_LARGE){
		asteroidHitPoints = ASTEROID_HIT_POINTS_LARGE;
		setRadius(ASTEROID_BASE_RADIUS);
	}

	if(state == AS_MEDIUM){
		asteroidHitPoints = ASTEROID_HIT_POINTS_MEDIUM;
		setRadius(ASTEROID_BASE_RADIUS / 2);

	}
	if(state == AS_SMALL){
		asteroidHitPoints = ASTEROID_HIT_POINTS_SMALL;
		setRadius(ASTEROID_BASE_RADIUS / 4);
	}

	//==================================================
	//Set velocity.

	//Decide x and y velocity directions (+ or -).
	int xDirection = 1;
	int yDirection = 1;
	if(rand() % 2)
		xDirection = -1;
	if(rand() % 2)
		yDirection = -1;

	float xVelocity = ((rand() % (ASTEROID_VELOCITY_RANGE + 1) + ASTEROID_VELOCITY_RANGE) * ASTEROID_VELOCITY_MULTIPLIER) * xDirection;
	float yVelocity = ((rand() % (ASTEROID_VELOCITY_RANGE + 1) + ASTEROID_VELOCITY_RANGE) * ASTEROID_VELOCITY_MULTIPLIER) * yDirection;

	setVelocity(xVelocity, yVelocity);

	//==================================================
	//Set location.

	//Set location for original asteroids.
	if(subAsteroid == false){
		//Decide if asteroid should be created at the top or left of screen.
		bool createOnYAxis = false; //If true creates asteroid of left side of screen, if false on top.
		if (rand() % 2)
			createOnYAxis = true;

		//Generate location.
		int asteroidLocation;

		if (createOnYAxis)
			asteroidLocation = rand() % settings.getWindowHeight();
		else
			asteroidLocation = rand() % settings.getWindowWidth();

		//Set Location.
		if(createOnYAxis)
			setLocation(0, static_cast<float>(rand() % settings.getWindowHeight()));
		else
			setLocation(static_cast<float>(rand() % settings.getWindowWidth()), 0);
	}

	//Set location for subasteroids.
	setLocation(parentLocationX, parentLocationY);

	//==================================================
	//Set rotational velocity.
	int asteroidRotDirection = 1;

	if(rand() % 2)
		asteroidRotDirection = -1;

	setRotationalVelocity(((static_cast<float>((rand() % ASTEROID_MAX_ROTATIONAL_VELOCITY) + 2) / 10)) * asteroidRotDirection);
}

//Destructor:
Asteroid::~Asteroid(){
	for(int x = 0; x < DUST_ARRAY_SIZE; x++)
		delete clouds[x];
}

//====================================================================================================
//Mutators:

//==================================================
//Function: damageAsteroid
//Description: Subracts damage from an asteroids hit points.
//
//Argument list:
//	damage(I): The amount to subtract from hit points.
//==================================================
void Asteroid::damageAsteroid(int damage){
	asteroidHitPoints -= damage;
}

//==================================================
//Function: destroyAsteroid
//Description: Sets an asteroids state to AS_DESTROYED,
//	sets its radius to 0, and creates just clouds.
//
//==================================================
void Asteroid::destroyAsteroid(){
	state = AS_DESTROYED;
	setRadius(0);

	for(int x = 0; x < DUST_ARRAY_SIZE; x++)
		clouds[x] = new DustCloud(settings, getVelocity(), getLocation());
}


//====================================================================================================
//Accessors:

//==================================================
//Function: getHitPoints
//Description: Returns the asteroids hit points.
//
//Return value:
//	The asteroids hit points.
//==================================================
int Asteroid::getHitPoints(){
	return asteroidHitPoints;
}

//==================================================
//Function: getState
//Description: Returns the asteroids state
//
//Return value:
//	The asteroids state.
//==================================================
AsteroidState Asteroid::getState(){
	return state;
}


//====================================================================================================
//Others:

//==================================================
//Function: draw
//Description: Selects a draw function.
//
//Argument list:
//	window(I): The window to be drawn on.
//==================================================
void Asteroid::draw(sf::RenderWindow& window, sf::Texture& dustCloud){
	if(state == AS_LARGE || state == AS_MEDIUM || state == AS_SMALL)
		drawAlive(window);
	else if(state = AS_DESTROYED)
		drawDestroyed(window, dustCloud);
}

//==================================================
//Function: drawAlive
//Description: Draws the asteroid to the screen.
//
//Argument list:
//	window(I): The window to be drawn on.
//==================================================
void Asteroid::drawAlive(sf::RenderWindow& window){

	sf::Vector2f midpoint(getRadius(), getRadius());

	//==================================================
	//Define asteroid:
	sf::CircleShape rocky(getRadius(), asteroidSides);
	rocky.setOrigin(midpoint);

	//==================================================
	//Define ghost asteroid:
	sf::CircleShape ghostRocky(getRadius(), asteroidSides);
	ghostRocky.setOrigin(midpoint);

	//==================================================
	//Set color:
	rocky.setFillColor(sf::Color(139, 69, 19));
	ghostRocky.setFillColor(sf::Color(139, 69, 19));

	//==================================================
	//Set location and rotation:

	//Variables
	float ghostRockyXPos;
	float ghostRockyYPos;

	//rocky
	rocky.setPosition(getLocation().x, getLocation().y);
	rocky.setRotation(getAngle());

	//ghostRocky
	if(getLocation().x < ASTEROID_BASE_RADIUS)
		ghostRockyXPos = settings.getWindowWidth() + getLocation().x;
	else if(getLocation().x > settings.getWindowWidth() - ASTEROID_BASE_RADIUS)
		ghostRockyXPos = (getLocation().x - settings.getWindowWidth());
	else
		ghostRockyXPos = getLocation().x;

	if(getLocation().y < ASTEROID_BASE_RADIUS)
		ghostRockyYPos = settings.getWindowHeight() + getLocation().y;
	else if(getLocation().y > settings.getWindowHeight() - ASTEROID_BASE_RADIUS)
		ghostRockyYPos = (getLocation().y - settings.getWindowHeight());
	else
		ghostRockyYPos = getLocation().y;

	ghostRocky.setPosition(ghostRockyXPos, ghostRockyYPos);
	ghostRocky.setRotation(getAngle());

	//Swap rockys location to ghostRockys
	if(getLocation().x <= getVelocity().x)
		setLocation(ghostRockyXPos, ghostRockyYPos);
	if(getLocation().x >= settings.getWindowWidth() + ASTEROID_BASE_RADIUS - getVelocity().x)
		setLocation(ghostRockyXPos, ghostRockyYPos);

	if(getLocation().y <= getVelocity().y)
		setLocation(ghostRockyXPos, ghostRockyYPos);
	if(getLocation().y >= settings.getWindowHeight() + ASTEROID_BASE_RADIUS - getVelocity().y)
		setLocation(ghostRockyXPos, ghostRockyYPos);

	//Draw:
	window.draw(rocky);

	if(getLocation().x < ASTEROID_BASE_RADIUS || getLocation().x > settings.getWindowWidth() - ASTEROID_BASE_RADIUS || getLocation().y < ASTEROID_BASE_RADIUS || getLocation().y > settings.getWindowHeight() - ASTEROID_BASE_RADIUS)
		window.draw(ghostRocky);
}

//==================================================
//Function: drawDestroyed
//Description: Draws a dust cloud to the screen
//
//Argument list:
//	window(I): The window to be drawn on.
//==================================================
void Asteroid::drawDestroyed(sf::RenderWindow& window, sf::Texture& dustCloud){

	for(int x = 0; x < DUST_ARRAY_SIZE; x++){
		clouds[x] -> drawDustCloud(window, dustCloud, explosionTimer);
	}

	explosionTimer++;
	if(explosionTimer >= ASTEROID_EXPLOSION_TIME){
		state = AS_GONE;
	}

}