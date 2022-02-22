#pragma once

#include "BasicEnemiesList.hpp"
#include "MediumEnemiesList.hpp"
#include "HardEnemiesList.hpp"
#include "Levels.hpp"
#include "time.h"

class Generator {

public:

    Generator();
		
    void generateBonusPoints(Levels* levels);

    void generateBonusLife(Levels* levels, int life);

    void generateBasicEnemies(Levels* levels, BasicEnemiesList* basicEnemies);

    void generateMediumEnemies(Levels* levels, MediumEnemiesList* mediumEnemies);

    void generateHardEnemies(Levels* levels, HardEnemiesList* hardEnemies);

};