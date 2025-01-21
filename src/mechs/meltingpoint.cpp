#include "meltingpoint.h"

#include "crawler.h"

MeltingPoint::MeltingPoint(Eigen::Vector2d positionArg,
                           Team teamArg,
                           int lvlArg,
                           Item* itemArg,
                           int* tArg,
                           std::list<Mech*>* mechsArg)
    : Mech(positionArg, teamArg, lvlArg, itemArg, tArg, mechsArg)
{
    initValues();
}

MeltingPointUnit::MeltingPointUnit(
    Eigen::Vector2i positionArg, Team teamArg, int lvlArg, int* tArg, std::list<Mech*>* mechsArg)
    : Unit(positionArg, teamArg, lvlArg, tArg, mechsArg)
{
}

MeltingPointLaser::MeltingPointLaser(Mech* mechArg, double relAngleArg)
    : LaserWeapon(mechArg, relAngleArg)
{
}

MeltingPointSpawnerWeapon::MeltingPointSpawnerWeapon(Mech* mechArg, double relAngleArg)
    : SpawnerWeapon(mechArg, relAngleArg)
{
    initTimer();
}

std::list<std::function<Weapon*(Mech*)>> MeltingPoint::getWeaponFactory()
{
    return {
        [](Mech* mech) { return new MeltingPointLaser(mech, 0); },
        // [](Mech* mech) { return new MeltingPointLaser(mech, PI / 2.0);
        // },
        // [](Mech* mech) { return new MeltingPointLaser(mech, -PI / 2.0);
        // },
        // [](Mech* mech) { return new MeltingPointLaser(mech, PI); },
        [](Mech* mech) { return new MeltingPointSpawnerWeapon(mech, 0); },
    };
}

Mech* MeltingPointSpawnerWeapon::makeMech()
{
    return new Crawler(
        getPosition() * 1.0001, mechOwn->team, 1, nullptr, mechOwn->t, mechOwn->mechs);
}

double MeltingPoint::getHpBase()
{
    return 30907;
}

double MeltingPoint::getSpeed()
{
    return 0.06;
}

double MeltingPoint::getTurnSpeed()
{
    return PI / 100.0;
}

bool MeltingPoint::getHasShield()
{
    return false;
}

bool MeltingPoint::getAttackable()
{
    return true;
}

double MeltingPoint::getRadius()
{
    return 2;
}

double MeltingPoint::getWeight()
{
    return 99999999;
}

std::string MeltingPoint::getString()
{
    return {"MP"};
}

Mech* MeltingPointUnit::makeMech(Eigen::Vector2d positionArg)
{
    return new MeltingPoint(positionArg, team, lvl, item, t, mechs);
}

int MeltingPointUnit::getCount()
{
    return 1;
}

Eigen::Vector2i MeltingPointUnit::getBaseSize()
{
    return {4, 4};
}

double MeltingPointLaser::getRange()
{
    return 11.5;
}
double MeltingPointLaser::getSplash()
{
    return 0.3;
}
double MeltingPointLaser::getAttack()
{
    return 1;
}
double MeltingPointLaser::getChargeRate()
{
    return 0.2;
}
double MeltingPointLaser::getRadius()
{
    return 0;  // mechOwn->getRadius() / 3.0;
}
bool MeltingPointLaser::getHack()
{
    return false;
}

double MeltingPointSpawnerWeapon::getRadius()
{
    return 0;  // mechOwn->getRadius();
}
double MeltingPointSpawnerWeapon::getRange()
{
    return MAX_RANGE;
}
double MeltingPointSpawnerWeapon::getTurnSpeed()
{
    return PI;
}
double MeltingPointSpawnerWeapon::getAngleSize()
{
    return PI;
}
int MeltingPointSpawnerWeapon::getAimTime()
{
    return 360;
}
int MeltingPointSpawnerWeapon::getLoadTime()
{
    return 1;
}
int MeltingPointSpawnerWeapon::getSalvoTime()
{
    return 8;
}
