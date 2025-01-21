#pragma once
#include "common.h"
#include "mech.h"
#include "unit.h"
#include "weapon.h"

class Crawler : public Mech
{
  public:
    Crawler(Eigen::Vector2d positionArg,
            Team teamArg,
            int lvlArg,
            Item* itemArg,
            int* tArg,
            std::list<Mech*>* mechsArg);
    ~Crawler() override = default;
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
    CrawlerUnit(Eigen::Vector2i positionArg,
                Team teamArg,
                int lvlArg,
                int* tArg,
                std::list<Mech*>* mechsArg);
    ~CrawlerUnit() override = default;
    int getCount() override;
    Eigen::Vector2i getBaseSize() override;
    Mech* makeMech(Eigen::Vector2d positionArg) override;
};

class CrawlerWeapon : public MeleeWeapon
{
  public:
    CrawlerWeapon(Mech* mechArg, double relAngleArg);
    ~CrawlerWeapon() override = default;
    double getSplash() override;
    double getAttack() override;
    int getAimTime() override;
};
