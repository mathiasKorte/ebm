#pragma once
#include "common.h"

class Mech
{
  public:
    Mech(Eigen::Vector2d _position,
         Team _team,
         int _lvl,
         Item* _item,
         int* _t,
         std::list<Mech*>* _mechs);
    virtual ~Mech() = default;

    Eigen::Vector2d position;
    Team team;
    int lvl;
    Item* item;
    int* t;
    std::list<Mech*>* mechs;

    double hp;
    double hpShield;
    double hpMax;
    Mech* obstacle;
    std::list<Weapon*> weapons;
    bool alive = true;
    double hackingDamage = 0.0;
    bool getsHacked = false;
    double angle;
    double blocking = 0.0;

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
