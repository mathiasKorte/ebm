#include "arclight.h"

Arclight::Arclight(Eigen::Vector2d positionArg,
                   Team teamArg,
                   int lvlArg,
                   Item* itemArg,
                   int* tArg,
                   std::list<Mech*>* mechsArg)
    : Mech(positionArg, teamArg, lvlArg, itemArg, tArg, mechsArg)
{
    initValues();
}

double Arclight::getHpBase()
{
    return 4414;
}
double Arclight::getSpeed()
{
    return 0.07;
}
double Arclight::getRadius()
{
    return 1;
}
double Arclight::getWeight()
{
    return 100;
}
double Arclight::getTurnSpeed()
{
    return PI / 10.0;
}
bool Arclight::getHasShield()
{
    return false;
}
bool Arclight::getAttackable()
{
    return true;
}
std::string Arclight::getString()
{
    return {"A"};
}
std::list<std::function<Weapon*(Mech*)>> Arclight::getWeaponFactory()
{
    return {
        [](Mech* mech) { return new ArclightWeapon(mech, 0); },
    };
}

ArclightUnit::ArclightUnit(
    Eigen::Vector2i positionArg, Team teamArg, int lvlArg, int* tArg, std::list<Mech*>* mechsArg)
    : Unit(positionArg, teamArg, lvlArg, tArg, mechsArg)
{
}

int ArclightUnit::getCount()
{
    return 1;
}
Mech* ArclightUnit::makeMech(Eigen::Vector2d positionArg)
{
    return new Arclight(positionArg, team, lvl, item, t, mechs);
}
Eigen::Vector2i ArclightUnit::getBaseSize()
{
    return {2, 2};
}

ArclightWeapon::ArclightWeapon(Mech* mechArg, double relAngleArg)
    : SpawnerWeapon(mechArg, relAngleArg)
{
    initTimer();
}

double ArclightWeapon::getRadius()
{
    return 0;
}
double ArclightWeapon::getRange()
{
    return 9.3;
}
double ArclightWeapon::getTurnSpeed()
{
    return PI / 10.0;
}
double ArclightWeapon::getAngleSize()
{
    return PI / 2.0;
}
int ArclightWeapon::getLoadTime()
{
    return 1;
}
int ArclightWeapon::getSalvoTime()
{
    return 1;
}
int ArclightWeapon::getAimTime()
{
    return 9;
}
Mech* ArclightWeapon::makeMech()
{
    return new ArclightShot(
        getPosition() * 1.0001, mechOwn->team, mechOwn->lvl, nullptr, mechOwn->t, mechOwn->mechs);
}

ArclightShot::ArclightShot(Eigen::Vector2d positionArg,
                           Team teamArg,
                           int lvlArg,
                           Item* itemArg,
                           int* tArg,
                           std::list<Mech*>* mechsArg)
    : Mech(positionArg, teamArg, lvlArg, itemArg, tArg, mechsArg)
{
    initValues();
}

double ArclightShot::getHpBase()
{
    return 1;
}
double ArclightShot::getSpeed()
{
    return 1.5;
}
double ArclightShot::getRadius()
{
    return 0.1;
}
double ArclightShot::getWeight()
{
    return 1;
}
double ArclightShot::getTurnSpeed()
{
    return PI;
}
bool ArclightShot::getHasShield()
{
    return false;
}
bool ArclightShot::getAttackable()
{
    return false;
}
std::string ArclightShot::getString()
{
    return {"S"};
}
std::list<std::function<Weapon*(Mech*)>> ArclightShot::getWeaponFactory()
{
    return {
        [](Mech* mech) { return new ArclightShotExplosion(mech, 0); },
    };
}

ArclightShotExplosion::ArclightShotExplosion(Mech* mechArg, double relAngleArg)
    : ExplosionWeapon(mechArg, relAngleArg)
{
}

double ArclightShotExplosion::getSplash()
{
    return 0.7;
}
double ArclightShotExplosion::getAttack()
{
    return 347;
}
bool ArclightShotExplosion::getSuicide()
{
    return true;
}
