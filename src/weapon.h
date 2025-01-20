#pragma once
#include "common.h"

class Weapon
{
  public:
    Weapon(Mech* _mech, double _relAngle);
    virtual ~Weapon() = default;

    Mech* mechOwn;
    double relAngle;
    Mech* target = nullptr;
    double angle;

    bool inTargetRange();
    bool inMechAngle(Mech* mech);
    void findTarget();
    void act();
    void turn();
    void splashAttack(Eigen::Vector2d pos, double attack);
    double gapToMech(Mech* mech);
    Eigen::Vector2d getPosition();
    double getMechAngle(Mech* mech);
    bool targetExists();

    virtual void shoot() = 0;
    virtual double getRange() = 0;
    virtual double getSplash() = 0;
    virtual bool getHack() = 0;
    virtual double getAttack() = 0;
    virtual double getRadius() = 0;
    virtual double getTurnSpeed() = 0;
    virtual double getAngleSize() = 0;
};

class LaserWeapon : public Weapon
{
  public:
    LaserWeapon(Mech* _mech, double _relAngle);
    virtual ~LaserWeapon() = default;

    double charge = 1;
    Mech* oldTarget = nullptr;

    void shoot() override;
    double getTurnSpeed() override;
    double getAngleSize() override;

    virtual double getChargeRate() = 0;
};

class MeleeWeapon : public Weapon
{
  public:
    MeleeWeapon(Mech* _mech, double _relAngle);
    virtual ~MeleeWeapon() = default;

    MyTimer* aimingTimer;

    void initTimer();

    void shoot() override;
    bool getHack() override;
    double getRadius() override;
    double getRange() override;
    double getTurnSpeed() override;
    double getAngleSize() override;

    virtual int getAimTime() = 0;
};

class SpawnerWeapon : public Weapon
{
  public:
    SpawnerWeapon(Mech* _mech, double _relAngle);
    virtual ~SpawnerWeapon() = default;

    MyTimer* aimingTimer;
    MyTimer* loadingTimer;
    MyTimer* salvoTimer;

    void initTimer();

    void shoot() override;
    bool getHack() override;
    double getSplash() override;
    double getAttack() override;

    virtual int getLoadTime() = 0;
    virtual int getSalvoTime() = 0;
    virtual int getAimTime() = 0;
    virtual Mech* makeMech() = 0;
};

class ExplosionWeapon : public Weapon
{
  public:
    ExplosionWeapon(Mech* _mech, double _relAngle);
    virtual ~ExplosionWeapon() = default;

    void shoot() override;
    bool getHack() override;
    double getRadius() override;
    double getRange() override;
    double getTurnSpeed() override;
    double getAngleSize() override;

    virtual bool getSuicide() = 0;
};