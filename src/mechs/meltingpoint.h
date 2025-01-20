#pragma once
#include "common.h"
#include "mech.h"
#include "unit.h"
#include "weapon.h"

class MeltingPoint : public Mech
{
  public:
    MeltingPoint(Eigen::Vector2d _position,
                 Team _team,
                 int _lvl,
                 Item* _item,
                 int* _t,
                 std::list<Mech*>* _mechs);

    double getHpBase() override;
    double getSpeed() override;
    double getRadius() override;
    double getWeight() override;
    double getTurnSpeed() override;
    bool getHasShield() override;
    bool getAttackable() override;
    std::string getString() override;
    std::list<std::function<Weapon*(Mech*)>> getWeaponFactory() override;
};

class MeltingPointUnit : public Unit
{
  public:
    MeltingPointUnit(Eigen::Vector2i _position,
                     Team _team,
                     int _lvl,
                     int* _t,
                     std::list<Mech*>* _mechs);

    int getCount() override;
    Mech* makeMech(Eigen::Vector2d _position) override;
    Eigen::Vector2i getBaseSize() override;
};

class MeltingPointMultiWeapon : public LaserWeapon
{
  public:
    MeltingPointMultiWeapon(Mech* _mech, double _relAngle);

    double getRange() override;
    double getSplash() override;
    double getAttack() override;
    double getChargeRate() override;
    double getRadius() override;
    bool getHack() override;
};

class MeltingPointSpawnerWeapon : public SpawnerWeapon
{
  public:
    MeltingPointSpawnerWeapon(Mech* _mech, double _relAngle);

    double getRadius() override;
    double getRange() override;
    double getTurnSpeed() override;
    double getAngleSize() override;
    int getLoadTime() override;
    int getSalvoTime() override;
    int getAimTime() override;
    Mech* makeMech() override;
};