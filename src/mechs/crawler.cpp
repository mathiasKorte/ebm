#include "crawler.h"

Crawler::Crawler(Eigen::Vector2d positionArg,
                 Team teamArg,
                 int lvlArg,
                 Item* itemArg,
                 int* tArg,
                 std::list<Mech*>* mechsArg)
    : Mech(positionArg, teamArg, lvlArg, itemArg, tArg, mechsArg)
{
    initValues();
}

CrawlerUnit::CrawlerUnit(
    Eigen::Vector2i positionArg, Team teamArg, int lvlArg, int* tArg, std::list<Mech*>* mechsArg)
    : Unit(positionArg, teamArg, lvlArg, tArg, mechsArg)
{
}

CrawlerWeapon::CrawlerWeapon(Mech* mechArg, double relAngleArg)
    : MeleeWeapon(mechArg, relAngleArg)
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
    return {"C"};
}

Mech* CrawlerUnit::makeMech(Eigen::Vector2d positionArg)
{
    return new Crawler(positionArg, team, lvl, item, t, mechs);
}

int CrawlerUnit::getCount()
{
    return 30;
}

Eigen::Vector2i CrawlerUnit::getBaseSize()
{
    return {5, 2};
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