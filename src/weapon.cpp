#include "weapon.h"

#include "mech.h"

Weapon::Weapon(Mech* mechArg, double relAngleArg)
    : mechOwn(mechArg)
    , relAngle(relAngleArg)
    , angle(relAngleArg)
{
}

bool Weapon::inTargetRange()
{
    return inMechAngle(target) && (gapToMech(target) < getRange());
}

bool Weapon::inMechAngle(Mech* mech)
{
    const double angleDiff = normalizeAngle(relAngle + mechOwn->angle - getMechAngle(mech));
    return std::abs(angleDiff) < getAngleSize();
}

void Weapon::findTarget()
{
    target = nullptr;

    for (Mech* mech : *(mechOwn->mechs))
        if ((mech->team != mechOwn->team) && mech->getAttackable()
            && (gapToMech(mech) + getRange() * static_cast<double>(!inMechAngle(mech))
                < gapToMech(target) + getRange() * static_cast<double>(!inMechAngle(target))))
            target = mech;
}

bool Weapon::targetExists() const
{
    if (target == nullptr)
        return false;
    return target->alive;
}

void Weapon::act()
{
    if (!targetExists() || !inTargetRange())
        findTarget();
    turn();
    if (inTargetRange() && (std::abs(angle - getMechAngle(target)) < SMALL))
        shoot();
}

void Weapon::splashAttack(Eigen::Vector2d pos, double attack)
{
    for (Mech* mech : *(mechOwn->mechs))
        if (mech->gapToPos(pos) < getSplash())
            mech->getAttacked(attack, getHack());
}

double Weapon::getMechAngle(Mech* mech)
{
    if (mech == nullptr)
        return normalizeAngle(relAngle + mechOwn->angle);

    Eigen::Vector2d deltaPosition = mech->position - getPosition();
    return std::atan2(deltaPosition.y(), deltaPosition.x());
}

void Weapon::turn()
{
    double targetAngle = 0;
    if (inTargetRange())
        targetAngle = getMechAngle(target);
    else
        targetAngle = normalizeAngle(relAngle + mechOwn->angle);

    const double angleDiff = normalizeAngle(targetAngle - angle);

    if (std::abs(angleDiff) <= getTurnSpeed())
        angle = targetAngle;
    else
    {
        angle += getTurnSpeed() * ((angleDiff < 0) ? -1 : 1);
        angle = normalizeAngle(angle);
    }
}

Eigen::Vector2d Weapon::getPosition()
{
    return mechOwn->position
        + Eigen::Vector2d(std::cos(relAngle + mechOwn->angle), std::sin(relAngle + mechOwn->angle))
        * getRadius();
}

double Weapon::gapToMech(Mech* mech)
{
    if (mech == nullptr)
        return std::numeric_limits<double>::max();
    return mech->gapToPos(getPosition());
}

void LaserWeapon::shoot()
{
    if (target == oldTarget)
    {
        charge += getChargeRate();
    } else
    {
        charge = 1;
    }
    oldTarget = target;

    splashAttack(target->position, getAttack() * charge * mechOwn->lvl);
}
void MeleeWeapon::shoot()
{
    aimingTimer->step();

    if (aimingTimer->done)
    {
        splashAttack(target->position, getAttack() * mechOwn->lvl);
        aimingTimer->reset();
    }
}
void SpawnerWeapon::shoot()
{
    aimingTimer->step();

    if (aimingTimer->done)
    {
        loadingTimer->step();
        if (loadingTimer->done)
        {
            Mech* mech = makeMech();
            mechOwn->mechs->push_front(mech);
            // mech->weapons.front()->setTarget(target, getTargetFixed());
            mech->weapons.front()->target = target;
            mech->act();

            loadingTimer->reset();
            salvoTimer->step();
            if (salvoTimer->done)
            {
                salvoTimer->reset();
                aimingTimer->reset();
            }
        }
    }
}
void ExplosionWeapon::shoot()
{
    splashAttack(getPosition(), getAttack());

    if (getSuicide())
        mechOwn->alive = false;
}

LaserWeapon::LaserWeapon(Mech* mechArg, double relAngleArg)
    : Weapon(mechArg, relAngleArg)
{
}
MeleeWeapon::MeleeWeapon(Mech* mechArg, double relAngleArg)
    : Weapon(mechArg, relAngleArg)
{
}
SpawnerWeapon::SpawnerWeapon(Mech* mechArg, double relAngleArg)
    : Weapon(mechArg, relAngleArg)
{
}
ExplosionWeapon::ExplosionWeapon(Mech* mechArg, double relAngleArg)
    : Weapon(mechArg, relAngleArg)
{
}

MeleeWeapon::~MeleeWeapon()
{
    delete aimingTimer;
}

SpawnerWeapon::~SpawnerWeapon()
{
    delete aimingTimer;
    delete loadingTimer;
    delete salvoTimer;
}

void MeleeWeapon::initTimer()
{
    aimingTimer = new MyTimer(getAimTime());
}
void SpawnerWeapon::initTimer()
{
    aimingTimer = new MyTimer(getAimTime());
    aimingTimer->time = aimingTimer->timeMax - 1;
    loadingTimer = new MyTimer(getLoadTime());
    salvoTimer = new MyTimer(getSalvoTime());
}

bool MeleeWeapon::getHack()
{
    return false;
}
bool SpawnerWeapon::getHack()
{
    return false;
}
bool ExplosionWeapon::getHack()
{
    return false;
}

double MeleeWeapon::getRadius()
{
    return mechOwn->getRadius();
}
double ExplosionWeapon::getRadius()
{
    return 0;
}

double MeleeWeapon::getRange()
{
    return mechOwn->getRadius() * 2.0;
}

double ExplosionWeapon::getRange()
{
    return 0.1;  // mechOwn->getRadius() * 10.0;
}

double LaserWeapon::getTurnSpeed()
{
    return PI;
}
double MeleeWeapon::getTurnSpeed()
{
    return PI;
}
double ExplosionWeapon::getTurnSpeed()
{
    return PI;
}

double LaserWeapon::getAngleSize()
{
    return PI;
}
double MeleeWeapon::getAngleSize()
{
    return PI / 10.0;
}
double ExplosionWeapon::getAngleSize()
{
    return PI / 10.0;
}

double SpawnerWeapon::getSplash()
{
    return 0;
}
double SpawnerWeapon::getAttack()
{
    return 0;
}
