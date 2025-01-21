#pragma once
#include "common.h"
#include "mech.h"
#include "unit.h"
#include "weapon.h"

class MeltingPoint : public Mech
{
  public:
    MeltingPoint(Eigen::Vector2d positionArg,
                 Team teamArg,
                 int lvlArg,
                 Item* itemArg,
                 int* tArg,
                 std::list<Mech*>* mechsArg);
    ~MeltingPoint() override = default;
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
    MeltingPointUnit(Eigen::Vector2i positionArg,
                     Team teamArg,
                     int lvlArg,
                     int* tArg,
                     std::list<Mech*>* mechsArg);
~MeltingPointUnit() override= default;
    int getCount() override;
    Mech* makeMech(Eigen::Vector2d positionArg) override;
    Eigen::Vector2i getBaseSize() override;
};

class MeltingPointLaser : public LaserWeapon
{
  public:
    MeltingPointLaser(Mech* mechArg, double relAngleArg);
    ~MeltingPointLaser() override = default;
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
    MeltingPointSpawnerWeapon(Mech* mechArg, double relAngleArg);
    ~MeltingPointSpawnerWeapon() override = default;
    double getRadius() override;
    double getRange() override;
    double getTurnSpeed() override;
    double getAngleSize() override;
    int getLoadTime() override;
    int getSalvoTime() override;
    int getAimTime() override;
    Mech* makeMech() override;
};