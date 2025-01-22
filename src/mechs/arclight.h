#pragma once
#include "../common.h"
#include "../mech.h"
#include "../unit.h"
#include "../weapon.h"

class Arclight : public Mech
{
  public:
    Arclight(Eigen::Vector2d positionArg,
             Team teamArg,
             int lvlArg,
             Item* itemArg,
             int* tArg,
             std::list<Mech*>* mechsArg);
    ~Arclight() override = default;
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

class ArclightUnit : public Unit
{
  public:
    ArclightUnit(Eigen::Vector2i positionArg,
                 Team teamArg,
                 int lvlArg,
                 int* tArg,
                 std::list<Mech*>* mechsArg);
    ~ArclightUnit() override = default;
    int getCount() override;
    Mech* makeMech(Eigen::Vector2d positionArg) override;
    Eigen::Vector2i getBaseSize() override;
};

class ArclightWeapon : public SpawnerWeapon
{
  public:
    ArclightWeapon(Mech* mechArg, double relAngleArg);
    ~ArclightWeapon() override = default;
    double getRadius() override;
    double getRange() override;
    double getTurnSpeed() override;
    double getAngleSize() override;
    int getLoadTime() override;
    int getSalvoTime() override;
    int getAimTime() override;
    Mech* makeMech() override;
};

class ArclightShot : public Mech
{
  public:
    ArclightShot(Eigen::Vector2d positionArg,
                 Team teamArg,
                 int lvlArg,
                 Item* itemArg,
                 int* tArg,
                 std::list<Mech*>* mechsArg);
    ~ArclightShot() override = default;
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

class ArclightShotExplosion : public ExplosionWeapon
{
  public:
    ArclightShotExplosion(Mech* mechArg, double relAngleArg);
    ~ArclightShotExplosion() override = default;
    double getSplash() override;
    double getAttack() override;
    bool getSuicide() override;
};