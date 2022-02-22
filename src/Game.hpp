#pragma once
#include "WindowsFunction.h"
#include "Levels.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Shots.hpp"
#include "BasicEnemiesList.hpp"
#include "MediumEnemiesList.hpp"
#include "HardEnemiesList.hpp"
#include "Generator.hpp"

class Game {

protected:
	Levels* levelsList;
	Player* player;
	Shots* playerShots;
	Shots* hardEnemyShots;
	BasicEnemiesList* basicEnemies;
	MediumEnemiesList* mediumEnemies;
	HardEnemiesList* hardEnemies;
	Generator* generator;
    
	
	
public:
	Game();

	void play();

	void update();

	void checkInputs(char input);

	void checkCollisions();

	void spawnBasicEnemies();

	void spawnMediumEnemies();

	void spawnHardEnemies();

	void checkChangeLevel();

	void changeLevel();

	void initializeGame();

};