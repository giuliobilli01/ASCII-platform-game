#pragma once
#include "WindowsFunction.h"
#include "Constant.h"
#include "Level.hpp"

class Shot {

public:

    int x;
    int y;
    Direction direction;
    Shot *nextShot;
    bool shouldStop;
    char ownerCharacter;
    

    Shot(int x, int y, Direction direction, char ownerCharacter);

    void updateShotPosition(Level* level);

    int getX();

    int getY();

    int CanIRight(Level*level);

    int CanILeft(Level*level);


};