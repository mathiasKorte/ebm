#pragma once
#include "common.h"

class Unit
{
  public:
    Unit(Eigen::Vector2i _position,
         Team _team,
         int _lvl,
         int* _t,
         std::list<Mech*>* _mechs);
    virtual ~Unit() = default;

    double experience;
    int lvl;
    int* t;
    bool transposed = false;
    void* mechContr;
    Team team;
    Item* item;
    Eigen::Vector2i position;
    std::list<Mech*>* mechs;

    void lvlUp();
    std::list<Mech*> spawn();
    Eigen::Vector2i getSize();

    virtual Mech* makeMech(Eigen::Vector2d _position) = 0;
    virtual int getCount() = 0;
    virtual Eigen::Vector2i getBaseSize() = 0;
};
