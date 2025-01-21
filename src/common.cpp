#include "common.h"

#include "mech.h"

auto normalizeAngle(double rad) -> double
{
    while (rad > PI)
        rad -= 2 * PI;
    while (rad < -PI)
        rad += 2 * PI;
    return rad;
}

Eigen::Vector2d clampVector(Eigen::Vector2d vec, Eigen::Vector2d min, Eigen::Vector2d max)
{
    const double clampedX = std::clamp(vec.x(), min.x(), max.x());
    const double clampedY = std::clamp(vec.y(), min.y(), max.y());
    return {clampedX, clampedY};
}

MyTimer::MyTimer(int timeMaxArg)
    : timeMax(timeMaxArg)
{
}

void MyTimer::step()
{
    time++;
    if (time == timeMax)
        done = true;
}
void MyTimer::reset()
{
    time = 0;
    done = false;
}

void mechCheck(Mech* mech)
{
    std::cout << "getRadius(): " << (mech->getRadius()) << "\n";
}

void mechsCheck(std::list<Mech*>* mechs)
{
    std::cout << "-------------------"
              << "\n";
    for (Mech* mech : *mechs)
        mechCheck(mech);
    std::cout << "-------------------"
              << "\n";
}
