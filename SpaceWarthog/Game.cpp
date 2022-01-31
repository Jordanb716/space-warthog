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

#include "Game.h"

//====================================================================================================
int game(Config inputSettings){

	//Variables.
	Config settings = inputSettings;

	Ship hawg(settings);
	int asteroidSpawnTimer = 0;

	GunSmoke* smoke[SMOKE_MAX_NUM] = {0};
	int smokeArrayPosition = 0;

	Bullet* bullet[BULLET_MAX_NUM] = {0};
	int bulletArrayPosition = 0;

	Asteroid* rocky[ASTEROID_MAX_NUM] = {0};
	for(int x = 0; x < settings.getInitialAsteroidCount(); x++)
		rocky[x] = new Asteroid(settings);

	//Load textures.
	sf::Texture gunSmoke;
	if(!gunSmoke.loadFromFile("Textures/GunSmoke.png")){
		// error...
	}

	sf::Texture dustCloud;
	if(!dustCloud.loadFromFile("Textures/DustCloud.png")){
		//Error...
	}

	//==================================================
	//Window settings.
	sf::ContextSettings winSettings;
	winSettings.antialiasingLevel = 8;

	//Window generation.
	sf::RenderWindow window(sf::VideoMode(settings.getWindowWidth(), settings.getWindowHeight()), 
		"Space Warthog: Asteroid Hunter", sf::Style::Titlebar | sf::Style::Close, winSettings);

	window.setFramerateLimit(FRAMERATE); //This causes loop to execute FRAMERATE number of times per second.

	//Place ship in middle of screen (window size / 2).
	hawg.setLocation(static_cast<float>(settings.getWindowWidth()/2), static_cast<float>(settings.getWindowHeight()/2));

	//====================================================================================================
	//Event loop:
	while (window.isOpen())
	{
		//==================================================
		//Handle user input (events and keyboard keys being pressed)
		sf::Event event;
		while (window.pollEvent(event))	{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//==================================================
		//Ship controls:

		if(hawg.getState() == SS_ALIVE){
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
				hawg.applyThrust(settings.getShipThrust());
				hawg.setEngineFiring(true);
			}
			else
				hawg.setEngineFiring(false);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
				hawg.rotateLeft();
				hawg.setTurningLeft(true);
			}
			else
				hawg.setTurningLeft(false);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
				hawg.rotateRight();
				hawg.setTurningRight(true);
			}
			else
				hawg.setTurningRight(false);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				hawg.fireGun(bullet, bulletArrayPosition, smoke, smokeArrayPosition);
			}
		}

		//==================================================
		//Check collision.

		//Check asteroid/ship collision.
		if(hawg.getState() == SS_ALIVE){
			for(int x = 0; x < ASTEROID_MAX_NUM; x++){
				if(rocky[x] != NULL && rocky[x] -> getState() != AS_DESTROYED){
					if(detectCollision(hawg, *rocky[x]))
						hawg.explode();
				}
			}
		}

		//Check fragment/asteroid collision.
		if(hawg.getState() == SS_EXPLODING)
			hawg.detectFragmentCollision(rocky);

		//Check bullet/asteroid collision.
		for(int x = 0; x < BULLET_MAX_NUM; x++){
			if(bullet[x] != NULL){
				for(int y = 0; y < ASTEROID_MAX_NUM; y++){
					if ((rocky[y] != NULL) && (bullet[x] != NULL)){
						if(detectCollision(*bullet[x], *rocky[y])){
							delete bullet[x];
							bullet[x] = NULL;
							rocky[y] -> damageAsteroid(1);
						}
					}
				}
			}
		}

		//Cycle asteroid states.
		cycleDamagedAsteroids(settings, rocky);

		//Find number of free asteroid spots.

		//Spawn new asteroids.
		if(asteroidSpawnTimer == 0){
			for(int x = 0, asteroidSpawned = 0; (x < ASTEROID_MAX_NUM) && (asteroidSpawned == 0); x++){
				if(rocky[x] == NULL){
					int asteroidChoice = rand() % 3;
					AsteroidState aState;

					//Decide size of new asteroid.
					if(asteroidChoice == 0)
						aState = AS_LARGE;
					else if (asteroidChoice == 1)
						aState = AS_MEDIUM;
					else
						aState = AS_SMALL;

					rocky[x] = new Asteroid(settings, aState);
					asteroidSpawned = 1;
				}
			}
		}
		asteroidSpawnTimer++;
		if(asteroidSpawnTimer >= settings.getAsteroidSpawnInterval())
			asteroidSpawnTimer = 0;

		//==================================================
		//Draw new frame.
		window.clear();

		//==================================================
		//Draw.

		//Draw asteroids.
		for(int x = 0; x < ASTEROID_MAX_NUM; x++){
			if (rocky[x] != NULL){
				rocky[x]->updateLocation(ASTEROID_BASE_RADIUS);
				rocky[x]->updateAngle();
				rocky[x]->draw(window, dustCloud);
			}
		}

		//Draw bullets.
		for(int x = 0; x < BULLET_MAX_NUM; x++){
			if(bullet[x] != NULL){
				bullet[x] -> updateLocation(10);
				if((bullet[x] -> getLocation().x < 0) || (bullet[x] -> getLocation().x > settings.getWindowWidth()) || (bullet[x] -> getLocation().y < 0 || (bullet[x] -> getLocation().y > settings.getWindowHeight()))){
					delete bullet[x];
					bullet[x] = NULL;
				}
				else
					bullet[x] -> drawBullet(window);
			}
		}

		//Draw hawg.
		hawg.updateLocation();
		hawg.draw(window);

		//Draw Effects.
		//Smoke
		for(int x = 0; x < SMOKE_MAX_NUM; x++){
			if(smoke[x] != NULL){
				smoke[x] -> updateLocation(10);
				if((smoke[x] -> getLocation().x < 0) || (smoke[x] -> getLocation().x > settings.getWindowWidth()) || (smoke[x] -> getLocation().y < 0 || (smoke[x] -> getLocation().y > settings.getWindowHeight()))){
					delete smoke[x];
					smoke[x] = NULL;
				}
				else if(smoke[x] -> getDecayTime() >= SMOKE_LIVE_TIME){
					delete smoke[x];
					smoke[x] = NULL;
				}
				else{
					smoke[x] -> drawGunSmoke(window, gunSmoke);
					smoke[x] -> incrementDecayTimer();
				}
			}
		}


		//Redisplay window.
		window.display();
	}
	return 0;
}

//==================================================
//Function: cycleDamagedAsteroids
//Description: Goes through an array of asteroid pointers,
//	finds asteroids that have been damaged down to zero hit points,
//	sets their state to destroyed and calls a function to create smaller ones.
//	Also ginds asteroids with state AS_GONE and deletes them.
//
//==================================================
void cycleDamagedAsteroids(Config settings, Asteroid* rocky[]){

	for(int x = 0; x < ASTEROID_MAX_NUM; x++){
		if(rocky[x] != NULL){
			if(rocky[x] -> getState() == AS_GONE){
				delete rocky[x];
				rocky[x] = NULL;
			}
			else if(rocky[x] -> getHitPoints() <= 0){
				createSubAsteroid(settings, rocky, x);
				rocky[x] -> destroyAsteroid();
			}
		}
	}
}

//==================================================
//Function: createSubAsteroid
//Description: Given an AsteroidState and an array of pointers,
//	creates subasteroids one size smaller than the given state
//	in appropriate number
//
//==================================================
void createSubAsteroid(Config settings, Asteroid* rocky[], int parentNumber){

	AsteroidState state = rocky[parentNumber] -> getState();

	if(state == AS_LARGE){
		for(int x = 0, y = 0; (x < ASTEROID_MAX_NUM) && (y < ASTEROID_CREATION_NUM_MEDIUM); x++){
			if(rocky[x] == NULL){
				rocky[x] = new Asteroid(settings, AS_MEDIUM, true, rocky[parentNumber] -> getLocation().x, rocky[parentNumber] -> getLocation().y);
				y++;
			}
		}
	}
	if(state == AS_MEDIUM){
		for(int x = 0, y = 0; (x < ASTEROID_MAX_NUM) && (y < ASTEROID_CREATION_NUM_MEDIUM); x++){
			if(rocky[x] == NULL){
				rocky[x] = new Asteroid(settings, AS_SMALL, true, rocky[parentNumber] -> getLocation().x, rocky[parentNumber] -> getLocation().y);
				y++;
			}
		}
	}
}