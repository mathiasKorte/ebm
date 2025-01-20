#include "mech.h"

#include "item.h"
#include "weapon.h"

Mech::Mech(Eigen::Vector2d _position,
           Team _team,
           int _lvl,
           Item* _item,
           int* _t,
           std::list<Mech*>* _mechs)
    : position(_position)
    , team(_team)
    , lvl(_lvl)
    , item(_item)
    , t(_t)
    , mechs(_mechs)

{
    // KEEP EMPTY!
}

double Mech::gapToMech(Mech* mech)
{
    if (mech == nullptr)
        return std::numeric_limits<double>::max();
    return gapToPos(mech->position) - mech->getRadius();
}

double Mech::gapToPos(Eigen::Vector2d mapPos)
{
    return (mapPos - position).norm() - getRadius();
}

void Mech::initValues()
{
    angle = (team == TEAM_GREEN) ? -PI / 2.0 : PI / 2.0;

    hpMax = getHpBase() * lvl;
    hp = hpMax;

    if (getHasShield())
        hpShield = hpMax;
    else
        hpShield = 0;

    for (std::function<Weapon*(Mech*)> createWeapon : getWeaponFactory())
        weapons.push_back(createWeapon(this));
}

void Mech::act()
{
    if (!getsHacked)
        hackingDamage = 0;
    getsHacked = false;

    for (Weapon* weapon : weapons)
        weapon->act();

    if (weapons.front()->targetExists() && !weapons.front()->inTargetRange())
        move();
    if (getAttackable())
        avoidObstacles();
}

void Mech::move()
{
    Eigen::Vector2d delta_position =
        weapons.front()->target->position - position;

    double targetAngle = std::atan2(delta_position.y(), delta_position.x());
    double angleDiff = normalizeAngle(targetAngle - angle);

    if (std::abs(angleDiff) <= getTurnSpeed())
    {
        angle = targetAngle;
        if (getSpeed() > delta_position.norm())
            position += delta_position;
        else
            position += delta_position * getSpeed() / delta_position.norm();
    } else
    {
        angle += getTurnSpeed() * ((angleDiff < 0) ? -1 : 1);
        angle = normalizeAngle(angle);
    }
}

void Mech::avoidObstacles()
{
    findObstacle();

    if (obstacle == nullptr)
        return;

    for (int i = 0; (gapToMech(obstacle) < 0) && (i < GIVE_UP_OBSTACLES); i++)
    {
        Eigen::Vector2d delta_position = obstacle->position - position;
        double len = -gapToMech(obstacle) / (delta_position.norm()) + SMALL;

        if (((obstacle->gapToMech(obstacle->obstacle) + gapToMech(obstacle)
              >= 0)
             && (obstacle->obstacle != this))
            || (obstacle->obstacle == this))
        {
            double weight_ratio =
                getWeight() / (getWeight() + obstacle->getWeight());
            position -= delta_position * len * (1.0 - weight_ratio);
            obstacle->position += delta_position * len * weight_ratio;
        } else
            position -= delta_position * len;

        if (gapToMech(obstacle) < 0)
            std::cout << "no success \n";

        findObstacle();
    }
}

void Mech::findObstacle()
{
    obstacle = nullptr;

    for (Mech* mech : *mechs)
        if ((gapToMech(mech) < gapToMech(obstacle)) && (mech != this)
            && mech->getAttackable())  // && (mech->team == team))
            obstacle = mech;
}

void Mech::getAttacked(double damage, bool hacking)
{
    if (!getAttackable())
        return;
    damage -= blocking;
    if (damage <= 0)
        return;

    if (hpShield > 0)
    {
        hpShield -= damage;
    } else if (hacking)
    {
        getsHacked = true;
        hackingDamage += damage;
        if (hp < hackingDamage)
        {
            if (team == TEAM_GREEN)
                team = TEAM_RED;
            else
                team = TEAM_GREEN;
        }
    } else
    {
        hp -= damage;
        alive = hp > 0;
    }
}