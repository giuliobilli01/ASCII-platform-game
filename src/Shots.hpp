#pragma once
#include "Shot.hpp"


class Shots {

protected:
    Shot *headShotList;
    Shot *currentShot;

public:
    Shots();

    void updateShots(Level* level);

    void prependShot(int x, int y, Direction direction, char ch);

    void deleteShot();

    Shot* foundShot(int x, int y);

    void deleteList(Level* level);

};