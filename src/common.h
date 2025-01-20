#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <list>
#include <string>

#include <eigen3/Eigen/Dense>

#define PI M_PI

constexpr double SMALL = 0.001;
constexpr double SMALL_ANGLE = (PI / 10.0);
constexpr int GIVE_UP_OBSTACLES = 10;
constexpr double MAX_RANGE = std::numeric_limits<double>::max() / 10.0;

class Mech;
class Unit;
class Item;
class Weapon;

class LaserWeapon;
class MeleeWeapon;
class SpawnerWeapon;
class ExplosionWeapon;

double normalizeAngle(double rad);
Eigen::Vector2d clampVector(Eigen::Vector2d vec,
                            Eigen::Vector2d min,
                            Eigen::Vector2d max);

class MyTimer
{
  public:
    MyTimer(int _timeMax);
    void step();
    void reset();
    bool done;
    int timeMax;
    int time;
};

enum Team
{
    TEAM_RED,
    TEAM_GREEN
};

void mechsCheck(std::list<Mech*>* mechs);
void mechCheck(Mech* mech);
