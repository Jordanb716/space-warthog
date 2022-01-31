//====================================================================================================
//Project: Bullet (class)
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class for storing bullet data.
//
//Revision date: Mar 06 2014
//====================================================================================================

#include "Bullet.h"

//====================================================================================================
//Constructor:
Bullet::Bullet(Config inputSettings) : SpaceObject(inputSettings){
	setRadius(2);
	setLocation(0, 0);
	setVelocity(0, 0);
}

Bullet::Bullet(Config settings, const FloatVector velocity, const FloatVector location, const float angle) : SpaceObject(settings){
	setRadius(2);
	setLocation(calculateRelativePosition(location, angle, 16).x, calculateRelativePosition(location, angle, 16).y);
	setVelocity(velocity.x, velocity.y);

	//Set angle.
	float angleMod = 0;
	angleMod = static_cast<float>(((rand() % 25) / 10.0));
	if(rand() % 2)
		angleMod *= -1;
	setAngle(angle + angleMod);

	applyThrust(BULLET_THRUST);
}

//Deconstructor:
Bullet::~Bullet(){

}


//====================================================================================================
//Mutators:


//====================================================================================================
//Accessors:


//====================================================================================================
//Others:

//==================================================
//Function: drawBullet
//Description: Draws the bullet on the given window.
//
//Argument list:
//	window(I): The window to be drawn on.
//==================================================
void Bullet::drawBullet(sf::RenderWindow& window){

	//Define Bullet
	sf::ConvexShape drawnBullet;

	drawnBullet.setPointCount(5);
	drawnBullet.setPoint(0, sf::Vector2f(0, 0));
	drawnBullet.setPoint(1, sf::Vector2f(-1, 1));
	drawnBullet.setPoint(2, sf::Vector2f(-1, 6));
	drawnBullet.setPoint(3, sf::Vector2f(1, 6));
	drawnBullet.setPoint(4, sf::Vector2f(1, 1));

	drawnBullet.setOrigin(0, 3);

	//Set color
	drawnBullet.setFillColor(sf::Color::White);

	//==================================================
	//Set locations and rotation.
	drawnBullet.setPosition(getLocation().x, getLocation().y);
	drawnBullet.setRotation(getAngle());

	//Draw
	window.draw(drawnBullet);
}