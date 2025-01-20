#include "crawler.h"

Crawler::Crawler(Eigen::Vector2d _position,
                 Team _team,
                 int _lvl,
                 Item* _item,
                 int* _t,
                 std::list<Mech*>* _mechs)
    : Mech(_position, _team, _lvl, _item, _t, _mechs)
{
    initValues();
}

CrawlerUnit::CrawlerUnit(Eigen::Vector2i _position,
                         Team _team,
                         int _lvl,
                         int* _t,
                         std::list<Mech*>* _mechs)
    : Unit(_position, _team, _lvl, _t, _mechs)
{
}

CrawlerWeapon::CrawlerWeapon(Mech* _mech, double _relAngle)
    : MeleeWeapon(_mech, _relAngle)
{
    initTimer();
}

std::list<std::function<Weapon*(Mech*)>> Crawler::getWeaponFactory()
{
    return {
        [](Mech* mech) { return new CrawlerWeapon(mech, 0.0); },
    };
}

double Crawler::getTurnSpeed()
{
    return PI / 10.0;
}

bool Crawler::getHasShield()
{
    return false;
}

bool Crawler::getAttackable()
{
    return true;
}

double Crawler::getHpBase()
{
    return 277;
}

double Crawler::getSpeed()
{
    return 0.16;
}

double Crawler::getRadius()
{
    return 5.0 / 10.0 / 2.0 * 0.7;
}

double Crawler::getWeight()
{
    return 1;
}

std::string Crawler::getString()
{
    return std::string("C");
}

Mech* CrawlerUnit::makeMech(Eigen::Vector2d _position)
{
    return new Crawler(_position, team, lvl, item, t, mechs);
}

int CrawlerUnit::getCount()
{
    return 30;
}

Eigen::Vector2i CrawlerUnit::getBaseSize()
{
    return Eigen::Vector2i(5, 2);
}

double CrawlerWeapon::getSplash()
{
    return 0;
}
double CrawlerWeapon::getAttack()
{
    return 79;
}
int CrawlerWeapon::getAimTime()
{
    return 6;
}