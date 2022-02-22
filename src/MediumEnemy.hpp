#pragma once

#include "WindowsFunction.h"
#include "Character.hpp"
#include "Constant.h"
#include "Shots.hpp"
#include "Level.hpp"
#include "time.h"

class MediumEnemy : public Character {

public:

    bool isAlive;

    int enemyLevelNumber;

    MediumEnemy* nextEnemy;
    
    MediumEnemy(int x, int y, int life ,int enemyLevelNumber);

    void moveMediumEnemy(Level* level, Shots* shots, Character* character);

    void positionEnemy(Level* level, char direction, Shots* shots, Character* character);

    int canGoRigth(Level* level, Shots* shots, Character* character);

    int canGoLeft(Level* level, Shots* shots, Character* character);

    bool canGoUp(Level* level, Shots* shots, Character* character);

    bool canGoDown(Level* level, Shots* shots, Character* character);

    void checkCollision(Level* level, Shots* shots);

    void isKilledByPlayer();

    bool isDead();

};