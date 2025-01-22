#pragma once
#include "common.h"
#include "mech.h"
#include "unit.h"
#include "weapon.h"

/**
 * @brief The class representing the game board.
 *
 * It contains all the Mechs and Units in the game. In the future, it will also manige ground effects like fire or oil.
 */
class Board
{
  public:
    std::list<Unit*> units;
    std::list<Mech*> mechs;
    std::list<Mech*> mechsDead;

    Board();
    ~Board();
    void step();
    int t = 0;
};