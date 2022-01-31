//====================================================================================================
//Project: Ship (class)
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class for storing ship data.
//
//Revision date: Mar 08 2014
//====================================================================================================

#include "Ship.h"

//====================================================================================================
//Constructor:
Ship::Ship(Config inputSettings) : SpaceObject(inputSettings){
	state = SS_ALIVE;
	engineIsFiring = false;
	gunIsFiring = false;
	fragmentDataSet = false;
	explosionTimer = 0;
	gunTimer = 0;
	setRadius(SHIP_RADIUS);

	setMaxLocation(settings.getWindowWidth(), settings.getWindowHeight());

	for(int x = 0; x < SHIP_FRAG_NUMBER; x++)
		debris[x] = new ShipFragment(settings);
}

//Destructor:
Ship::~Ship(){
	for(int x = 0; x < SHIP_FRAG_NUMBER; x++)
		delete debris[x];
}


//====================================================================================================
//Mutators:

//==================================================
//Function: explode
//Description: Sets ShipState to SS_EXPLODING.
//
//==================================================
void Ship::explode(){
	state = SS_EXPLODING;
}

//==================================================
//Function: setEngineFiring
//Description: Sets the engine firing state.
//
//Argument list:
//	engineState(I):
//		true: Engine is firing.
//		false: Engine is not firing.
//==================================================
void Ship::setEngineFiring(bool engineState){
	engineIsFiring = engineState;
}

//==================================================
//Function: setGunFiring
//Description: Sets the gun firing state.
//
//Argument list:
//	gunState(I):
//		true: Gun is firing.
//		false:  Gun is not firing.
//==================================================
void Ship::setGunFiring(bool gunState){
	gunIsFiring = gunState;
}

//==================================================
//Function: setTurningLeft
//Description: Sets the left turn state.
//
//Argument list:
//	leftTurnState(I):
//		true: Ship is turning left.
//		false: Ship is not turning left.
//==================================================
void Ship::setTurningLeft(bool leftTurnState){
	isTurningLeft = leftTurnState;
}

//==================================================
//Function: setTurningRight
//Description: Sets the right turn state.
//
//Argument list:
//	rightTurnState(I):
//		true: Ship is turning right.
//		false: Ship is not turning right.
//==================================================
void Ship::setTurningRight(bool rightTurnState){
	isTurningRight = rightTurnState;
}

//==================================================
//Function: detectFragmentCollision
//Description: Checks each fragment in the ship against an object
//	for collision, and makes the fragments bounce off.
//
//Argument list:
//	object(I): The object to check each fragment against.
//==================================================
void Ship::detectFragmentCollision(Asteroid* asteroidArray[]){

	//Detect Collision.
	for(int x = 0; x < SHIP_FRAG_NUMBER; x++){
		if(debris[x] != NULL){
			for(int y = 0; y < ASTEROID_MAX_NUM; y++){
				if ((asteroidArray[y] != NULL) && (debris[x] != NULL)){
					if(detectCollision(*debris[x], *asteroidArray[y])){

						//Thrust debris away from collision.
						debris[x] -> setAngle(180 + calculateAngle(*asteroidArray[y], *debris[x]));
						debris[x] -> applyThrust(0.1);
					}
				}
			}
		}
	}
}


//====================================================================================================
//Accessors:

//==================================================
//Function: checkEngineFiring
//Description: Checks if the engine is firing
//	
//Return (bool):
//	true: Engine is firing.
//	false: Engine is not firing.
//==================================================
bool Ship::checkEngineFiring(){
	return engineIsFiring;
}

//==================================================
//Function: checkGunFiring
//Description: Checks if the gun is firing;
//	
//Return (bool):
//	true: Gun is firing.
//	false: Gun is not firing.
//==================================================
bool Ship::checkGunFiring(){
	return gunIsFiring;
}

//==================================================
//Function: checkTurningLeft
//Description: Checks if ship is turning left.
//	
//Return (bool):
//	true: Ship is turning left
//	false: Ship is not turning left.
//==================================================
bool Ship::checkTurningLeft(){
	return isTurningLeft;
}

//==================================================
//Function: checkTurningRight
//Description: Checks if ship is turning right.
//	
//Return (bool):
//	true: Ship is turning right.
//	false: Ship is not turning right.
//==================================================
bool Ship::checkTurningRight(){
	return isTurningRight;
}

//==================================================
//Function: checkIsExploding
//Description: Checks if ship is exploding (SS_EXPLODING is set).
//	
//Return (bool):
//	true: Ship is exploding.
//	false: Ship is not exploding.
//==================================================
bool Ship::checkIsExploding(){
	if(state == SS_EXPLODING)
		return true;
	else
		return false;
}

//==================================================
//Function: getState
//Description: Checks if ship is exploding (SS_EXPLODING is set).
//	
//Return (ShipState):
//	SS_ALIVE: Ship is alive.
//	SS_EXPLODING: Ship is exploding.
//	SS_GONE: Ship is gone.
//==================================================
ShipState Ship::getState(){
	return state;
}


//====================================================================================================
//Others:

//==================================================
//Function: rotateLeft
//Description: Rotate the ship to the left.
//
//==================================================
void Ship::rotateLeft(){
	if(state == SS_ALIVE)
		SpaceObject::rotateLeft(settings.getShipTurnRate());
}

//==================================================
//Function: rotateRight
//Description: Rotate the ship to the right.
//
//==================================================
void Ship::rotateRight(){
	if(state == SS_ALIVE)
		SpaceObject::rotateRight(settings.getShipTurnRate());
}

//==================================================
//Function: fireGun
//Description: Produces bullets on a regular interval and thrusts ship backwards. (recoil)
//
//==================================================
void Ship::fireGun(Bullet* bulletArray[], int& bulletArrayPosition, GunSmoke* smokeArray[], int& smokeArrayPosition){

	if(gunTimer == 0){ //If true fire gun, else wait.

		//Create bullet, overwrite if nessessary.
		if(bulletArray[bulletArrayPosition] != NULL){
			delete bulletArray[bulletArrayPosition];
			bulletArray[bulletArrayPosition] = 0;
		}

		bulletArray[bulletArrayPosition] = new Bullet(settings, getVelocity(), getLocation(), getAngle());
		bulletArrayPosition++;
		if(bulletArrayPosition >= BULLET_MAX_NUM){
			bulletArrayPosition = 0;
		}

		//Create smoke, overwrite if nessessary.
		if(smokeArray[smokeArrayPosition] != NULL){
			delete smokeArray[smokeArrayPosition];
			smokeArray[smokeArrayPosition] = 0;
		}

		smokeArray[smokeArrayPosition] = new GunSmoke(settings, getVelocity(), getLocation(), getAngle());
		smokeArrayPosition++;
		if(smokeArrayPosition >= SMOKE_MAX_NUM){
			smokeArrayPosition = 0;
		}
	}
	gunTimer++;

	if(gunTimer >= SHIP_GUN_DELAY_TIME){
		gunTimer = 0;
	}

	//Thrust
	applyThrust(-0.5 * settings.getShipThrust());
}

//==================================================
//Function: draw
//Description: Calls a draw function for the ship appropriate to its state (alive, exploding, gone)
//
//Argument list:
//	window(I): The window to be drawn on.
//==================================================
void Ship::draw(sf::RenderWindow& window){
	if(state == SS_ALIVE)
		drawAliveShip(window);

	else if(state == SS_EXPLODING)
		drawExplodingShip(window);
}

//==================================================
//Function: drawAliveShip
//Description: Draws the ship to the screen.
//
//Argument list:
//	window(I): The window to be drawn on.
//==================================================
void Ship::drawAliveShip(sf::RenderWindow& window){

	sf::Vector2f midpoint(0,16);

	//Define nose:
	sf::ConvexShape nose;
	nose.setPointCount(3);
	nose.setPoint(0, sf::Vector2f(0, 0));
	nose.setPoint(1, sf::Vector2f(1, 1));
	nose.setPoint(2, sf::Vector2f(-1, 1));
	nose.setOrigin(midpoint);

	//Define body:
	sf::ConvexShape body;
	body.setPointCount(4);
	body.setPoint(0, sf::Vector2f(-1, 1));
	body.setPoint(1, sf::Vector2f(1, 1));
	body.setPoint(2, sf::Vector2f(1, 29));
	body.setPoint(3, sf::Vector2f(-1, 29));
	body.setOrigin(midpoint);

	//Define wing:
	sf::ConvexShape wing;
	wing.setPointCount(4);
	wing.setPoint(0, sf::Vector2f(-18, 13));
	wing.setPoint(1, sf::Vector2f(18, 13));
	wing.setPoint(2, sf::Vector2f(18, 18));
	wing.setPoint(3, sf::Vector2f(-18, 18));
	wing.setOrigin(midpoint);

	//Define nacelle1:
	sf::ConvexShape nacelle1;
	nacelle1.setPointCount(4);
	nacelle1.setPoint(0, sf::Vector2f(-5, 20));
	nacelle1.setPoint(1, sf::Vector2f(-3, 20));
	nacelle1.setPoint(2, sf::Vector2f(-3, 26));
	nacelle1.setPoint(3, sf::Vector2f(-5, 26));
	nacelle1.setOrigin(midpoint);

	//Define nacelle2:
	sf::ConvexShape nacelle2;
	nacelle2.setPointCount(4);
	nacelle2.setPoint(0, sf::Vector2f(3, 20));
	nacelle2.setPoint(1, sf::Vector2f(5, 20));
	nacelle2.setPoint(2, sf::Vector2f(5, 26));
	nacelle2.setPoint(3, sf::Vector2f(3, 26));
	nacelle2.setOrigin(midpoint);

	//Define tailWing:
	sf::ConvexShape tailWing;
	tailWing.setPointCount(4);
	tailWing.setPoint(0, sf::Vector2f(-5, 29));
	tailWing.setPoint(1, sf::Vector2f(5, 29));
	tailWing.setPoint(2, sf::Vector2f(5, 32));
	tailWing.setPoint(3, sf::Vector2f(-5, 32));
	tailWing.setOrigin(midpoint);

	//==================================================
	//Conditional:
	//Define engineFlame1
	sf::ConvexShape engineFlame1;
	engineFlame1.setPointCount(3);
	engineFlame1.setPoint(0, sf::Vector2f(-5, 27));
	engineFlame1.setPoint(1, sf::Vector2f(-3, 27));
	engineFlame1.setPoint(2, sf::Vector2f(-4, 30));
	engineFlame1.setOrigin(midpoint);

	//Define engineFlame2
	sf::ConvexShape engineFlame2;
	engineFlame2.setPointCount(3);
	engineFlame2.setPoint(0, sf::Vector2f(3, 27));
	engineFlame2.setPoint(1, sf::Vector2f(5, 27));
	engineFlame2.setPoint(2, sf::Vector2f(4, 30));
	engineFlame2.setOrigin(midpoint);

	//Define RCSLeftFront
	sf::ConvexShape RCSLeftFront;
	RCSLeftFront.setPointCount(3);
	RCSLeftFront.setPoint(0, sf::Vector2f(-18, 12));
	RCSLeftFront.setPoint(1, sf::Vector2f(-16, 12));
	RCSLeftFront.setPoint(2, sf::Vector2f(-17, 11));
	RCSLeftFront.setOrigin(midpoint);

	//Define RCSLeftRear
	sf::ConvexShape RCSLeftRear;
	RCSLeftRear.setPointCount(3);
	RCSLeftRear.setPoint(0, sf::Vector2f(-18, 19));
	RCSLeftRear.setPoint(1, sf::Vector2f(-16, 19));
	RCSLeftRear.setPoint(2, sf::Vector2f(-17, 20));
	RCSLeftRear.setOrigin(midpoint);

	//Define RCSRightFront
	sf::ConvexShape RCSRightFront;
	RCSRightFront.setPointCount(3);
	RCSRightFront.setPoint(0, sf::Vector2f(18, 12));
	RCSRightFront.setPoint(1, sf::Vector2f(16, 12));
	RCSRightFront.setPoint(2, sf::Vector2f(17, 11));
	RCSRightFront.setOrigin(midpoint);

	//Define RCSRightRear
	sf::ConvexShape RCSRightRear;
	RCSRightRear.setPointCount(3);
	RCSRightRear.setPoint(0, sf::Vector2f(18, 19));
	RCSRightRear.setPoint(1, sf::Vector2f(16, 19));
	RCSRightRear.setPoint(2, sf::Vector2f(17, 20));
	RCSRightRear.setOrigin(midpoint);

	//==================================================
	//Color parts.

	//nose:
	nose.setFillColor(sf::Color(184, 196, 196));
	nose.setOutlineThickness(1);
	nose.setOutlineColor(sf::Color(184, 196, 196));

	//body
	body.setFillColor(sf::Color(184, 196, 196));
	body.setOutlineThickness(1);
	body.setOutlineColor(sf::Color(184, 196, 196));

	//wing
	wing.setFillColor(sf::Color(184, 196, 196));
	wing.setOutlineThickness(1);
	wing.setOutlineColor(sf::Color(184, 196, 196));

	//nacelle1
	nacelle1.setFillColor(sf::Color(184, 196, 196));
	nacelle1.setOutlineThickness(1);
	nacelle1.setOutlineColor(sf::Color(0, 0, 0));

	//nacelle2
	nacelle2.setFillColor(sf::Color(184, 196, 196));
	nacelle2.setOutlineThickness(1);
	nacelle2.setOutlineColor(sf::Color(0, 0, 0));

	//tailWing
	tailWing.setFillColor(sf::Color(184, 196, 196));
	tailWing.setOutlineThickness(1);
	tailWing.setOutlineColor(sf::Color(184, 196, 196));

	//engineFlame1
	engineFlame1.setFillColor(sf::Color(152, 234, 255));
	engineFlame1.setOutlineThickness(1);
	engineFlame1.setOutlineColor(sf::Color(44, 117, 255));

	//engineFlame2
	engineFlame2.setFillColor(sf::Color(152, 234, 255));
	engineFlame2.setOutlineThickness(1);
	engineFlame2.setOutlineColor(sf::Color(44, 117, 255));

	//RCSLeftFront
	RCSLeftFront.setFillColor(sf::Color(255, 255, 255));
	RCSLeftFront.setOutlineThickness(1);
	RCSLeftFront.setOutlineColor(sf::Color(44, 117, 255));

	//RCSLeftRear
	RCSLeftRear.setFillColor(sf::Color(255, 255, 255));
	RCSLeftRear.setOutlineThickness(1);
	RCSLeftRear.setOutlineColor(sf::Color(44, 117, 255));

	//RCSRightFront
	RCSRightFront.setFillColor(sf::Color(255, 255, 255));
	RCSRightFront.setOutlineThickness(1);
	RCSRightFront.setOutlineColor(sf::Color(44, 117, 255));

	//RCSRightRear
	RCSRightRear.setFillColor(sf::Color(255, 255, 255));
	RCSRightRear.setOutlineThickness(1);
	RCSRightRear.setOutlineColor(sf::Color(44, 117, 255));

	//==================================================
	//Set part locations and rotation.
	nose.setPosition(getLocation().x, getLocation().y);
	nose.setRotation(getAngle());

	body.setPosition(getLocation().x, getLocation().y);
	body.setRotation(getAngle());

	wing.setPosition(getLocation().x, getLocation().y);
	wing.setRotation(getAngle());

	nacelle1.setPosition(getLocation().x, getLocation().y);
	nacelle1.setRotation(getAngle());

	nacelle2.setPosition(getLocation().x, getLocation().y);
	nacelle2.setRotation(getAngle());

	tailWing.setPosition(getLocation().x, getLocation().y);
	tailWing.setRotation(getAngle());

	engineFlame1.setPosition(getLocation().x, getLocation().y);
	engineFlame1.setRotation(getAngle());

	engineFlame2.setPosition(getLocation().x, getLocation().y);
	engineFlame2.setRotation(getAngle());

	RCSLeftFront.setPosition(getLocation().x, getLocation().y);
	RCSLeftFront.setRotation(getAngle());

	RCSLeftRear.setPosition(getLocation().x, getLocation().y);
	RCSLeftRear.setRotation(getAngle());

	RCSRightFront.setPosition(getLocation().x, getLocation().y);
	RCSRightFront.setRotation(getAngle());

	RCSRightRear.setPosition(getLocation().x, getLocation().y);
	RCSRightRear.setRotation(getAngle());


	//==================================================
	//Draw parts:
	window.draw(nose);
	window.draw(body);
	window.draw(wing);
	window.draw(nacelle1);
	window.draw(nacelle2);
	window.draw(tailWing);

	//Conditional:
	//Engine Flames
	if(checkEngineFiring()){
		window.draw(engineFlame1);
		window.draw(engineFlame2);
	}

	//RCS (Turning)
	if(checkTurningLeft()){
		window.draw(RCSLeftFront);
		window.draw(RCSRightRear);
	}
	if(checkTurningRight()){
		window.draw(RCSRightFront);
		window.draw(RCSLeftRear);
	}
}

//==================================================
//Function: drawExplodingShip
//Description: Draws the ship explosion and wreckage to the screen.
//
//Argument list:
//	window(I): The window to be drawn on.
//==================================================
void Ship::drawExplodingShip(sf::RenderWindow& window){

	//Set Fragments.
	if(fragmentDataSet == false){
		for(int x = 0; x < SHIP_FRAG_NUMBER; x++)
			debris[x] -> setFragData(getVelocity(), getLocation());
		fragmentDataSet = true;
	}

	//Decay fragments.
	if(explosionTimer >= SHIP_FLASH_TIME * 2){
		for(int x = 0; x < SHIP_FRAG_NUMBER; x++)
			if(debris[x] != NULL){
				debris[x] -> decrementDecayTimer();
				if(debris[x] -> getDecayTime() == 0){
					debris[x] -> decay();
					debris[x] = NULL;
				}
			}
	}

	//Draw Fragments.
	for(int x = 0; x < SHIP_FRAG_NUMBER; x++){
		if((debris[x] != NULL) && (debris[x] -> getState() == FRAG_ALIVE)){
			debris[x] -> drawDebris(window);
		}
	}

	//Draw Flash.
	if(explosionTimer < SHIP_FLASH_TIME){
		sf::CircleShape flash(SHIP_RADIUS, 30);

		flash.setRadius(SHIP_RADIUS + explosionTimer / 2);
		flash.setOrigin(flash.getRadius(), flash.getRadius());

		flash.setFillColor(sf::Color(255, 51, 51, (255 - 255 * explosionTimer / SHIP_FLASH_TIME)));

		flash.setPosition(getLocation().x, getLocation().y);
		flash.setRotation(getAngle());

		window.draw(flash);
	}

	//Increment timer.
	explosionTimer++;

	//Clean up post-explosion.
	if(explosionTimer >= SHIP_EXPLOSION_TIME){
		explosionTimer = 0;
		fragmentDataSet = false;

		for(int x = 0; x < SHIP_FRAG_NUMBER; x++)
			if (debris[x] != NULL){
				delete debris[x];
				debris[x] = NULL;
			}
			state = SS_GONE;
	}
}
