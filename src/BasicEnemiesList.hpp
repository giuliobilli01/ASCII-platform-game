#pragma once
#include "BasicEnemy.hpp"

class BasicEnemiesList {

protected:
    BasicEnemy* headBasicEnemiesList;
    BasicEnemy* currentBasicEnemy;

public:

    BasicEnemiesList();

    void prependBasicEnemy(int x, int y, int levelNumber, int enemyLife);

    void updateBasicEnemies(Level* level, Shots* shots);

    void deleteBasicEnemy();

    void deleteBasicEnemyWithXY(Level* level, int x, int y);

    BasicEnemy* foundBasicEnemy(int x, int y);

};