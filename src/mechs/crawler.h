#pragma once
#include "common.h"
#include "mech.h"
#include "unit.h"
#include "weapon.h"

class Crawler : public Mech
{
  public:
    Crawler(Eigen::Vector2d _position,
            Team _team,
            int _lvl,
            Item* _item,
            int* _t,
            std::list<Mech*>* _mechs);
    double getHpBase() override;
    std::list<std::function<Weapon*(Mech*)>> getWeaponFactory() override;
    double getSpeed() override;
    double getRadius() override;
    double getWeight() override;
    double getTurnSpeed() override;
    bool getHasShield() override;
    bool getAttackable() override;
    std::string getString() override;
};

class CrawlerUnit : public Unit
{
  public:
    CrawlerUnit(Eigen::Vector2i _position,
                Team _team,
                int _lvl,
                int* _t,
                std::list<Mech*>* _mechs);
    static int count;
    int getCount() override;
    Eigen::Vector2i getBaseSize() override;
    static Eigen::Vector2i size;
    Mech* makeMech(Eigen::Vector2d _position) override;
};

class CrawlerWeapon : public MeleeWeapon
{
  public:
    CrawlerWeapon(Mech* _mech, double _relAngle);

    double getSplash() override;
    double getAttack() override;
    int getAimTime() override;
};
