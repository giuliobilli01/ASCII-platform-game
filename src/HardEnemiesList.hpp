#pragma once
#include "HardEnemy.hpp"

class HardEnemiesList {

protected:
    HardEnemy* headHardEnemiesList;
    HardEnemy* currentHardEnemy;

public:

    HardEnemiesList();

    void prependHardEnemy(int x, int y, int levelNumber, int enemyLife);

    void updateHardEnemies(Level* level, Shots* playerShots, Shots* myShots, Character* character);

    void deleteHardEnemy();

    HardEnemy* foundHardEnemy(int x, int y);

    void deleteHardEnemyWithXY(Level* level, int x, int y);

};