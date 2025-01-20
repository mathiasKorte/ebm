#include "meltingpoint.h"

#include "crawler.h"

MeltingPoint::MeltingPoint(Eigen::Vector2d _position,
                           Team _team,
                           int _lvl,
                           Item* _item,
                           int* _t,
                           std::list<Mech*>* _mechs)
    : Mech(_position, _team, _lvl, _item, _t, _mechs)
{
    initValues();
}

MeltingPointUnit::MeltingPointUnit(Eigen::Vector2i _position,
                                   Team _team,
                                   int _lvl,
                                   int* _t,
                                   std::list<Mech*>* _mechs)
    : Unit(_position, _team, _lvl, _t, _mechs)
{
}

MeltingPointMultiWeapon::MeltingPointMultiWeapon(Mech* _mech, double _relAngle)
    : LaserWeapon(_mech, _relAngle)
{
}

MeltingPointSpawnerWeapon::MeltingPointSpawnerWeapon(Mech* _mech,
                                                     double _relAngle)
    : SpawnerWeapon(_mech, _relAngle)
{
    initTimer();
}

std::list<std::function<Weapon*(Mech*)>> MeltingPoint::getWeaponFactory()
{
    return {
        [](Mech* mech) { return new MeltingPointMultiWeapon(mech, 0); },
        // [](Mech* mech) { return new MeltingPointMultiWeapon(mech, PI / 2.0);
        // },
        // [](Mech* mech) { return new MeltingPointMultiWeapon(mech, -PI / 2.0);
        // },
        // [](Mech* mech) { return new MeltingPointMultiWeapon(mech, PI); },
        [](Mech* mech) { return new MeltingPointSpawnerWeapon(mech, 0); },
    };
}

Mech* MeltingPointSpawnerWeapon::makeMech()
{
    return new Crawler(getPosition() * 1.0001,
                       mechOwn->team,
                       1,
                       nullptr,
                       mechOwn->t,
                       mechOwn->mechs);
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
    return std::string("MP");
}

Mech* MeltingPointUnit::makeMech(Eigen::Vector2d _position)
{
    return new MeltingPoint(_position, team, lvl, item, t, mechs);
}

int MeltingPointUnit::getCount()
{
    return 1;
}

Eigen::Vector2i MeltingPointUnit::getBaseSize()
{
    return Eigen::Vector2i(4, 4);
}

double MeltingPointMultiWeapon::getRange()
{
    return 11.5;
}
double MeltingPointMultiWeapon::getSplash()
{
    return 0.3;
}
double MeltingPointMultiWeapon::getAttack()
{
    return 1;
}
double MeltingPointMultiWeapon::getChargeRate()
{
    return 0.2;
}
double MeltingPointMultiWeapon::getRadius()
{
    return 0;  // mechOwn->getRadius() / 3.0;
}
bool MeltingPointMultiWeapon::getHack()
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
