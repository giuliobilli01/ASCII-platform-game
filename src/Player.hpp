#pragma once
#include "WindowsFunction.h"
#include "Character.hpp"
#include "Constant.h"
#include "Shots.hpp"
#include "Levels.hpp"
#include "BasicEnemiesList.hpp"
#include "MediumEnemiesList.hpp"
#include "HardEnemiesList.hpp"


class Player: public Character {

protected:

	int points;
	changeLevelConditions shouldChangeLevel;

public:

	Player(int x, int y, int life, Direction direction, int points);

	void checkPlayerInput(char input, Levels* levels, Shots* shots, BasicEnemiesList* basicEnemies, MediumEnemiesList* mediumEnemies, HardEnemiesList* hardEnemies);

	void movePlayer(char input, Levels* levels, BasicEnemiesList* basicEnemies, MediumEnemiesList* mediumEnemies, HardEnemiesList* hardEnemies);

	int getPoints();

	void increasePoints(int inc);
	
	void updatePlayerPosition(char input , Level* level); 

	void checkCollisionWithShot(Level* level, Shots* shots);

	void printPlayerPoints(Level* level);
 
	void printPlayerLevel(Level* level);

	void printPlayerData(Level* level);

	void checkPoints(Level* level);

	void setShouldChangeLevel(changeLevelConditions condition);

	void spawnPlayerInNewLevel(Level* level, char doorType);

	changeLevelConditions getShouldChangeLevel();

	bool canShotRight(Level* level);

	bool canShotLeft(Level* level);

};