#pragma once
#include "MediumEnemy.hpp"

class MediumEnemiesList {

protected:

    MediumEnemy* headMediumEnemiesList;
    MediumEnemy* currentMediumEnemy;

public:

    MediumEnemiesList();

    void prependMediumEnemy(int x, int y, int levelNumber, int enemyLife);

    void updateMediumEnemies(Level* level, Shots* shots, Character* character);

    void deleteMediumEnemy();

    MediumEnemy* foundMediumEnemy(int x, int y);

};


