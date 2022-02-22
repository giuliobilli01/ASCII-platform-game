#pragma once
#include "WindowsFunction.h"
#include "Character.hpp"
#include "Constant.h"
#include "Shots.hpp"
#include "Level.hpp"
#include "time.h"

class HardEnemy : public Character {

public:

    bool isAlive;

    int enemyLevelNumber;

    Direction direction;

    HardEnemy* nextEnemy;
    
    HardEnemy(int x, int y, int life , Direction direction, int enemyLevelNumber);

    void shotHardEnemy(Level* level, Shots* myShots, Character* character);

    void checkCollision(Level* level, Shots* playerShots);

    bool isDead();

    void updateHardEnemy(Level* level, Shots* myShots, Character* character);

    void isKilledByPlayer();

};