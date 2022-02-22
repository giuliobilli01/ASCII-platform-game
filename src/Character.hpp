#pragma once
#include "WindowsFunction.h"
#include "Constant.h"
#include "Shots.hpp"
#include "Levels.hpp"

class Character {

protected:

    int x;
    int y;
    int life;
    Direction direction;

public:

    Character(int x, int y, int life, Direction direction);

    Character();

    Character(int x, int y, int life);

    int getX();

    int getY();

    int getLIfe();

    Direction getDirection();

    void decreaseLife(int dec);

    void increaseLife(int inc);

    void printLife(Level* level);
    
};