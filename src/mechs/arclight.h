#pragma once
#include "common.h"
#include "mech.h"
#include "unit.h"
#include "weapon.h"

class Arclight : public Mech
{
  public:
    Arclight(Eigen::Vector2d _position,
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

class ArclightUnit : public Unit
{
  public:
    ArclightUnit(Eigen::Vector2i _position,
                 Team _team,
                 int _lvl,
                 int* _t,
                 std::list<Mech*>* _mechs);

    int getCount() override;
    Mech* makeMech(Eigen::Vector2d _position) override;
    Eigen::Vector2i getBaseSize() override;
};

class ArclightWeapon : public SpawnerWeapon
{
  public:
    ArclightWeapon(Mech* _mech, double _relAngle);

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
    ArclightShot(Eigen::Vector2d _position,
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

class ArclightShotExplosion : public ExplosionWeapon
{
  public:
    ArclightShotExplosion(Mech* _mech, double _relAngle);

    double getSplash() override;
    double getAttack() override;
    bool getSuicide() override;
};