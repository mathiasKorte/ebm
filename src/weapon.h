#pragma once
#include "common.h"

/**
 * @brief Represents each attacking entity in the game.
 *
 * Each Mech has a list of Weapons, while Weapons do the actual attacking (of other Mechs). This can
 * be done by 1) Laser, 2) Melee, 3) Spawner, or 4) Explosion Weapons; which are all subclasses of
 * Weapon.
 */
class Weapon
{
  public:
    Weapon(Mech* mechArg, double relAngleArg);
    virtual ~Weapon() = default;

    Mech* mechOwn;
    double relAngle;
    Mech* target = nullptr;
    double angle = 0;

    bool inTargetRange();
    bool inMechAngle(Mech* mech);
    void findTarget();
    void act();
    void turn();
    void splashAttack(Eigen::Vector2d pos, double attack);
    double gapToMech(Mech* mech);
    Eigen::Vector2d getPosition();
    double getMechAngle(Mech* mech);
    bool targetExists() const;

    virtual void shoot() = 0;
    virtual double getRange() = 0;
    virtual double getSplash() = 0;
    virtual bool getHack() = 0;
    virtual double getAttack() = 0;
    virtual double getRadius() = 0;
    virtual double getTurnSpeed() = 0;
    virtual double getAngleSize() = 0;
};

/**
 * @brief Direct growing damage weapon.
 *
 * Inherits from Weapon. Attacks do direct damage to the target Mech; damage grows over time. Meant
 * for MeltingPoints, Steelballs, and (maybe?) Hackers.
 */
class LaserWeapon : public Weapon
{
  public:
    LaserWeapon(Mech* mechArg, double relAngleArg);
    ~LaserWeapon() override = default;

    double charge = 1;
    Mech* oldTarget = nullptr;

    void shoot() override;
    double getTurnSpeed() override;
    double getAngleSize() override;

    virtual double getChargeRate() = 0;
};

/**
 * @brief Close range weapon.
 *
 * Inherits from Weapon. Attacks do direct damage to the target Mech. Meant for Crawlers, Rhinos and
 * Worms.
 */
class MeleeWeapon : public Weapon
{
  public:
    MeleeWeapon(Mech* mechArg, double relAngleArg);
    ~MeleeWeapon() override;

    MyTimer* aimingTimer = nullptr;

    void initTimer();

    void shoot() override;
    bool getHack() override;
    double getRadius() override;
    double getRange() override;
    double getTurnSpeed() override;
    double getAngleSize() override;

    virtual int getAimTime() = 0;
};

/**
 * @brief Cannon/Spawner weapon.
 *
 * Inherits from Weapon. Multi-purpose: 1) gun (shoots bullets), 2) missile-launcher (shoots
 * rockets), or 3) spawner (spawns Crawlers, etc). (This works because all moving elements in the
 * game are Mechs.)
 */
class SpawnerWeapon : public Weapon
{
  public:
    SpawnerWeapon(Mech* mechArg, double relAngleArg);
    ~SpawnerWeapon() override;

    MyTimer* aimingTimer = nullptr;
    MyTimer* loadingTimer = nullptr;
    MyTimer* salvoTimer = nullptr;

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

/**
 * @brief Explosion/Impact/Suicide weapon.
 *
 * Inherits from Weapon. Meant for everything exploding like rockets, Rhinos or Arclight-bullets.
 */
class ExplosionWeapon : public Weapon
{
  public:
    ExplosionWeapon(Mech* mechArg, double relAngleArg);
    ~ExplosionWeapon() override = default;

    void shoot() override;
    bool getHack() override;
    double getRadius() override;
    double getRange() override;
    double getTurnSpeed() override;
    double getAngleSize() override;

    virtual bool getSuicide() = 0;
};