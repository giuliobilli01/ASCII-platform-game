#pragma once

#include "WindowsFunction.h"
#include "Character.hpp"
#include "Constant.h"
#include "Shots.hpp"
#include "Level.hpp"

class BasicEnemy : public Character {

public:

    bool isAlive;

    int enemyLevelNumber;

    BasicEnemy* nextEnemy;
    
    BasicEnemy(int x, int y, int life, int enemyLevelNumber);
    
    void checkCollision(Level* level, Shots* shots);

    bool isDead();

    void updateBasicEnemy(Level* level);

    void isKilledByPlayer();

};