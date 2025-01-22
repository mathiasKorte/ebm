#pragma once
#include "common.h"

/**
 * @brief The core class representing each moving entity in the game.
 *
 * Each moving entity in the game is a Mech. Crawlers, MeltingPoints, and Arclights are all
 * subclasses of Mech. Same goes for all rockets and bullets. Mainly Mechs can 1) move, 2) be attacked,
 * 3) carry Weapons. (While Weapons do the actual attacking.)
 */

class Mech
{
  public:
    Mech(Eigen::Vector2d positionArg,
         Team teamArg,
         int lvlArg,
         Item* itemArg,
         int* tArg,
         std::list<Mech*>* mechsArg);
    virtual ~Mech();

    Eigen::Vector2d position;
    Team team;
    int lvl;
    Item* item;
    int* t;
    std::list<Mech*>* mechs;

    double hp = 0;
    double hpShield = 0;
    double hpMax = 0;
    Mech* obstacle = nullptr;
    std::list<Weapon*> weapons;
    bool alive = true;
    double hackingDamage = 0;
    bool getsHacked = false;
    double angle = 0;
    double blocking = 0;

    void act();
    void findObstacle();
    void initValues();
    double gapToMech(Mech* mech);
    double gapToPos(Eigen::Vector2d mapPos);
    void getAttacked(double damage, bool hacking);
    void avoidObstacles();
    void move();

    virtual bool getAttackable() = 0;
    virtual double getHpBase() = 0;
    virtual double getSpeed() = 0;
    virtual double getRadius() = 0;
    virtual double getWeight() = 0;
    virtual double getTurnSpeed() = 0;
    virtual bool getHasShield() = 0;
    virtual std::string getString() = 0;
    virtual std::list<std::function<Weapon*(Mech*)>> getWeaponFactory() = 0;
};
