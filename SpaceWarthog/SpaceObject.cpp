//====================================================================================================
//Header: SpaceObject (class) 
//Author: Jordan Bergmann
//Environment: Visual Studio 2012 (C++)
//
//Description: A class with general functions for objects in space.
//
//Revision date: Mar 09 2014
//====================================================================================================

#include "SpaceObject.h"

//====================================================================================================
//Constructor:
SpaceObject::SpaceObject(Config inputSettings){
	settings = inputSettings;
	locationBoundaries.x = settings.getWindowWidth();
	locationBoundaries.y = settings.getWindowHeight();
	objectLocation.x = 0;
	objectLocation.y = 0;
	objectVelocity.x = 0;
	objectVelocity.y = 0;
	objectRotVelocity = 0;
	objectAngle = 0;
	objectRadius = 0;
	decayTimer = 0;
}

//====================================================================================================
//Mutators:

//==================================================
//Function: setMaxLocation
//Description: Sets the boundaries on where the object can go.
//
//Argument list:
//	boundaries(I): A vector with the X and Y positions for the boundary.
//==================================================
void SpaceObject::setMaxLocation(int newXBoundary, int newYBoundary){
	locationBoundaries.x = newXBoundary;
	locationBoundaries.y = newYBoundary;
}

//==================================================
//Function: setLocation
//Description: Sets the objects location, and corrects if it goes out of bounds (wraps around to the other side).
//
//Argument list:
//	x(I): X coordinate.
//	y(I): Y coordinate.
//==================================================
void SpaceObject::setLocation(float newX, float newY){

	//Set location.
	objectLocation.x = newX;
	objectLocation.y = newY;
}

//==================================================
//Function: setVelocity
//Description: Sets the objects velocity.
//
//Argument list:
//	velocityX(I): X component of velocity.
//	velocityY(I): Y component of velocity.
//==================================================
void SpaceObject::setVelocity(float newVelocityX, float newVelocityY){
	objectVelocity.x = newVelocityX;
	objectVelocity.y = newVelocityY;
}

//==================================================
//Function: setRotationalVelocity
//Description: Sets the objects rotational velocity.
//
//Argument list:
//	newRotVelocity(I): New rotational velocity.
//==================================================
void SpaceObject::setRotationalVelocity(float newRotVelocity){
	objectRotVelocity = newRotVelocity;
}

//==================================================
//Function: setAngle
//Description: Sets the object angle.
//
//Argument list:
//	angle(I): Object angle in degrees. (0 at top, rotates clockwise.)
//==================================================
void SpaceObject::setAngle(float newAngle){

	//Set angle.
	objectAngle = newAngle;

	//Correct for out of bounds.
	if (objectAngle >= 360)
		objectAngle -= 360;

	if (objectAngle < 0)
		objectAngle += 360;
}

//==================================================
//Function: setRadius
//Description: Sets the object radius.
//
//Argument list:
//	radius(I): Object radius.
//==================================================
void SpaceObject::setRadius(float newRadius){
	objectRadius = newRadius;
}

//==================================================
//Function: cngVelocity
//Description: Adds the input x and y velocity to the
//	objects current velocity.
//
//Argument list:
//	deltaVx(I): x component of velocity to add.
//	deltaVy(I): y component of velocity to add.
//==================================================
void SpaceObject::cngVelocity(float deltaVx, float deltaVy){

	//Add velocities together.
	objectVelocity.x += deltaVx;
	objectVelocity.y += deltaVy;

	//Out of bounds correction.
	if (objectLocation.x > locationBoundaries.x)
		objectLocation.x -= locationBoundaries.x;
	if (objectLocation.y > locationBoundaries.y)
		objectLocation.y -= locationBoundaries.y;

	if (objectLocation.x < 0)
		objectLocation.x += locationBoundaries.x;
	if (objectLocation.y < 0)
		objectLocation.y += locationBoundaries.y;
}

//==================================================
//Function: cngAngle
//Description: Adds the input angle to the objects current angle.
//
//Argument list:
//	deltaA(I): Angle to add.
//==================================================
void SpaceObject::cngAngle(float deltaA){
	objectAngle += deltaA;
}

//==================================================
//Function: cngRadius
//Description: Adds the input radius to the objects radius.
//
//Argument list:
//	deltaR(I): Radius value to add.
//==================================================
void SpaceObject::cngRadius(float deltaR){
	objectRadius += deltaR;
}

//==================================================
//Function: setDecayTimer
//Description: Sets the decay timer to the given value.
//
//==================================================
void SpaceObject::setDecayTimer(int time){
	decayTimer = time;
}

//==================================================
//Function: incrementDecayTimer
//Description: Adds one to decayTimer.
//
//==================================================
void SpaceObject::incrementDecayTimer(){
	decayTimer++;
}

//==================================================
//Function: decrementDecayTimer
//Description: Subtracts one from decayTimer.
//
//==================================================
void SpaceObject::decrementDecayTimer(){
	decayTimer--;
}


//====================================================================================================
//Accessors:

//==================================================
//Function: getRadius
//Description: Returns the objects radius.
//
//Return value:
//	The objects radius
//==================================================
float SpaceObject::getRadius(){
	return objectRadius;
}

//==================================================
//Function: getLocation
//Description: Returns the objects location.
//
//Return value:
//	The objects location.
//==================================================
FloatVector SpaceObject::getLocation(){
	return objectLocation;
}

//==================================================
//Function: getVelocity
//Description: Returns the objects velocity.
//
//Return value:
//	The objects velocity.
//==================================================
FloatVector SpaceObject::getVelocity(){
	return objectVelocity;
}

//==================================================
//Function: getAngle
//Description: Returns the objects angle.
//
//Return value:
//	The objects angle
//==================================================
float SpaceObject::getAngle(){
	return objectAngle;
}

//==================================================
//Function: getDecayTime
//Description: Gets decayTimer (counts down to decide when fragments decay and stop drawing).
//
//Return (int):
//	decayTime
//==================================================
int SpaceObject::getDecayTime(){
	return decayTimer;
}


//====================================================================================================
//Others:

//==================================================
//Function: applyThrust
//Description: Applies speed to the object in the direction it is facing.
//
//==================================================
void SpaceObject::applyThrust(double thrust){
	float forcex = static_cast<float>(sin((objectAngle)*PI / 180) * thrust);
	float forcey = static_cast<float>(cos((objectAngle)*PI / 180) * thrust);
	objectVelocity.x = objectVelocity.x + forcex;
	objectVelocity.y = objectVelocity.y - forcey;
}

//==================================================
//Function: rotateLeft
//Description: Rotate the object to the left at given speed.
//
//==================================================
void SpaceObject::rotateLeft(float turnSpeed){

	//Subract from objects current angle.
	objectAngle -= turnSpeed;

	//Out of bounds correction.
	if (objectAngle < 0)
		objectAngle += 360;
}

//==================================================
//Function: rotateRight
//Description: Rotate the object to the right at given speed.
//
//==================================================
void SpaceObject::rotateRight(float turnSpeed){

	//Add to objects current angle.
	objectAngle += turnSpeed;

	//Out of bounds correction.
	if (objectAngle >= 360)
		objectAngle -= 360;
}

//==================================================
//Function: updateLocation
//Description: Updates an objects location based on the current velocity.
//	If a radius is given, boundary checking will
//	allow objects to be offscreen for the same
//	distance as their radius.
//==================================================
void SpaceObject::updateLocation(float givenRadius){

	//Add velocity to location.
	objectLocation.x += objectVelocity.x;
	objectLocation.y += objectVelocity.y;

	//Check and correct for the object going out of bounds.
	if(givenRadius){
		if (objectLocation.x > locationBoundaries.x + givenRadius)
			objectLocation.x -= locationBoundaries.x + givenRadius;
		if (objectLocation.y > locationBoundaries.y + givenRadius)
			objectLocation.y -= locationBoundaries.y + givenRadius;

		if (objectLocation.x < 0 - givenRadius)
			objectLocation.x += locationBoundaries.x + givenRadius;
		if (objectLocation.y < 0 - givenRadius)
			objectLocation.y += locationBoundaries.y + givenRadius;
	}

	else {
		if (objectLocation.x > locationBoundaries.x)
			objectLocation.x -= locationBoundaries.x;
		if (objectLocation.y > locationBoundaries.y)
			objectLocation.y -= locationBoundaries.y;

		if (objectLocation.x < 0)
			objectLocation.x += locationBoundaries.x;
		if (objectLocation.y < 0)
			objectLocation.y += locationBoundaries.y;
	}
}

//==================================================
//Function: updateAngle
//Description: Updates an objects angle based on the current rotational velocity.
//
//==================================================
void SpaceObject::updateAngle(){

	//Add rotational velocity to angle.
	objectAngle += objectRotVelocity;

	//Out of bounds correction.
	if (objectAngle < 0)
		objectAngle += 360;

	if (objectAngle >= 360)
		objectAngle -= 360;
}

//====================================================================================================
//Friends:

//==================================================
//Function: detectCollision
//Description: Checks if two objects are colliding (radii overlap).
//
//Argument list:
//	object1(I): First object.
//	object2(I): Second object.
//
//Return:
//	true: Objects are colliding.
//	false: Objects are not colliding.
//==================================================
bool detectCollision(SpaceObject object1, SpaceObject object2){

	//Calculate distance between objects using distance formula.
	double distance = sqrt(pow((object2.objectLocation.x - object1.objectLocation.x), 2) + pow((object2.objectLocation.y - object1.objectLocation.y), 2));

	//Compare distance calculated to combined radius to determine if objects are colliding.
	if(distance < (object1.objectRadius + object2.objectRadius))
		return true;
	else
		return false;
}

//==================================================
//Function: calculateAngle
//Description: Calculates the angle in degrees between two objects.
//
//Argument list:
//	object1(I): First object.
//	object2(I): Second object.
//
//Return:
//	float: The calculated angle.
//==================================================
float calculateAngle(SpaceObject object1, SpaceObject object2){
	double xDistance = ((object1.getLocation().x) - (object2.getLocation().x));
	double yDistance = ((object1.getLocation().y) - (object2.getLocation().y));

	double angle = (atan(yDistance / xDistance) * (180 / PI));

	if(xDistance >=0)
		angle += 90;
	else if(xDistance < 90)
		angle += 270;

	return (static_cast<float>(angle));
}

//==================================================
//Function: calculateVelocity
//Description: Calculates the velocity of an object using the pythagorean theorem.
//
//Argument list:
//	object(I): Object whose velocity will be calculated.
//
//Return:
//	float: The calculated velocity.
//==================================================
double calculateVelocity(SpaceObject object){
	return sqrt(pow(fabs(object.getVelocity().x), 2) + (pow(fabs(object.getVelocity().y), 2)));
}

//==================================================
//Function: calculateDeltaV
//Description: Calculates the deltaV
//
//Argument list:
//	object1(I): First object.
//	object2(I): Second object.
//
//Return:
//	Vector: The calculated delta V;
//==================================================
/*Vector calculateDeltaV(SpaceObject object1, SpaceObject object2){

Vector deltaV;

deltaV.x = (object1.getVelocity().x + object2.getVelocity.x);
deltaV.y = (object1.getVelocity().y + object2.getVelocity.y);

return deltaV;
} */

//==================================================
//Function: calculateRelativePosition
//Description: Calculates the coordinates of a position
//	given an origin, an angle, and a distance.
//
//Argument list:
//	origin(I): The location to calculate from.
//	angle(I): The angle in degrees from vertical clockwise.
//	distance(I): The distance from the origin in pixels.
//
//Return:
//	FloatVector: The desired coordinates
//==================================================
FloatVector calculateRelativePosition(FloatVector origin, float angle, float distance){

	FloatVector result;

	result.x = static_cast<float>(origin.x + (distance * cos((angle + 270) * (PI / 180))));
	result.y = static_cast<float>(origin.y + (distance * sin((angle + 270) * (PI / 180))));

	return result;
}