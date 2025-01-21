#include "mech.h"

#include "item.h"
#include "weapon.h"

Mech::Mech(Eigen::Vector2d positionArg,
           Team teamArg,
           int lvlArg,
           Item* itemArg,
           int* tArg,
           std::list<Mech*>* mechsArg)
    : position(std::move(positionArg))
    , team(teamArg)
    , lvl(lvlArg)
    , item(itemArg)
    , t(tArg)
    , mechs(mechsArg)

{
    // KEEP EMPTY!
}

Mech::~Mech()
{
    for (Weapon* weapon : weapons)
        delete weapon;
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
    angle = (team == Team::green) ? -PI / 2.0 : PI / 2.0;

    hpMax = getHpBase() * lvl;
    hp = hpMax;

    if (getHasShield())
        hpShield = hpMax;
    else
        hpShield = 0;

    for (const std::function<Weapon*(Mech*)>& createWeapon : getWeaponFactory())
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
    Eigen::Vector2d deltaPosition = weapons.front()->target->position - position;

    const double targetAngle = std::atan2(deltaPosition.y(), deltaPosition.x());
    const double angleDiff = normalizeAngle(targetAngle - angle);

    if (std::abs(angleDiff) <= getTurnSpeed())
    {
        angle = targetAngle;
        if (getSpeed() > deltaPosition.norm())
            position += deltaPosition;
        else
            position += deltaPosition * getSpeed() / deltaPosition.norm();
    } else
    {
        angle += getTurnSpeed() * ((angleDiff < 0) ? -1 : 1);
        angle = normalizeAngle(angle);
    }
}

void Mech::avoidObstacles()
{
    findObstacle();

    for (int i = 0; (gapToMech(obstacle) < 0) && (i < GIVE_UP_OBSTACLES); i++)
    {
        if(obstacle==nullptr)
            return;
        const Eigen::Vector2d deltaPosition = obstacle->position - position;
        const double len = (-gapToMech(obstacle) / (deltaPosition.norm())) + SMALL;

        if (((obstacle->gapToMech(obstacle->obstacle) + gapToMech(obstacle) >= 0)
             && (obstacle->obstacle != this))
            || (obstacle->obstacle == this))
        {
            const double weightRatio = getWeight() / (getWeight() + obstacle->getWeight());
            position -= deltaPosition * len * (1.0 - weightRatio);
            obstacle->position += deltaPosition * len * weightRatio;
        } else
            position -= deltaPosition * len;

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
            if (team == Team::green)
                team = Team::red;
            else
                team = Team::green;
        }
    } else
    {
        hp -= damage;
        alive = hp > 0;
    }
}