#pragma once
#include <list>

class Mech;

enum Team
{
    TEAM_RED,
    TEAM_BLUE,
};



class Board
{
  public:
    std::list<Mech*> mechs;
    Board(bool check);
    void step();
    u_int64_t t = 0;
};