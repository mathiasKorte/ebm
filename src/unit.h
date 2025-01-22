#pragma once
#include "common.h"

/**
 * @brief The standard groups of Mechs.
 *
 * Manage the spawning of Mechs, their Items, and their experience.
 */
class Unit
{
  public:
    Unit(Eigen::Vector2i positionArg,
         Team teamArg,
         int lvlArg,
         int* tArg,
         std::list<Mech*>* mechsArg);
    virtual ~Unit();

    Eigen::Vector2i position;
    Team team;
    int lvl;
    int* t;
    std::list<Mech*>* mechs;

    Item* item;
    double experience = 0;
    bool transposed = false;

    void lvlUp();
    std::list<Mech*> spawn();
    Eigen::Vector2i getSize();

    virtual Mech* makeMech(Eigen::Vector2d positionArg) = 0;
    virtual int getCount() = 0;
    virtual Eigen::Vector2i getBaseSize() = 0;
};
