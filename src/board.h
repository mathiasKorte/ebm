#pragma once
#include "common.h"
#include "mech.h"
#include "unit.h"
#include "weapon.h"

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