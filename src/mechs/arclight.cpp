#include "arclight.h"

Arclight::Arclight(Eigen::Vector2d _position,
                   Team _team,
                   int _lvl,
                   Item* _item,
                   int* _t,
                   std::list<Mech*>* _mechs)
    : Mech(_position, _team, _lvl, _item, _t, _mechs)
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
    return std::string("A");
}
std::list<std::function<Weapon*(Mech*)>> Arclight::getWeaponFactory()
{
    return {
        [](Mech* mech) { return new ArclightWeapon(mech, 0); },
    };
}

ArclightUnit::ArclightUnit(Eigen::Vector2i _position,
                           Team _team,
                           int _lvl,
                           int* _t,
                           std::list<Mech*>* _mechs)
    : Unit(_position, _team, _lvl, _t, _mechs)
{
}

int ArclightUnit::getCount()
{
    return 1;
}
Mech* ArclightUnit::makeMech(Eigen::Vector2d _position)
{
    return new Arclight(_position, team, lvl, item, t, mechs);
}
Eigen::Vector2i ArclightUnit::getBaseSize()
{
    return Eigen::Vector2i(2, 2);
}

ArclightWeapon::ArclightWeapon(Mech* _mech, double _relAngle)
    : SpawnerWeapon(_mech, _relAngle)
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
    return new ArclightShot(getPosition() * 1.0001,
                            mechOwn->team,
                            1,
                            nullptr,
                            mechOwn->t,
                            mechOwn->mechs);
}

ArclightShot::ArclightShot(Eigen::Vector2d _position,
                           Team _team,
                           int _lvl,
                           Item* _item,
                           int* _t,
                           std::list<Mech*>* _mechs)
    : Mech(_position, _team, _lvl, _item, _t, _mechs)
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
    return std::string("S");
}
std::list<std::function<Weapon*(Mech*)>> ArclightShot::getWeaponFactory()
{
    return {
        [](Mech* mech) { return new ArclightShotExplosion(mech, 0); },
    };
}

ArclightShotExplosion::ArclightShotExplosion(Mech* _mech, double _relAngle)
    : ExplosionWeapon(_mech, _relAngle)
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
