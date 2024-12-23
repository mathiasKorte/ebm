#include <cmath>
#include <iostream>

#include "mechs.h"

#define SMALL 0.001

Crawler::Crawler(double _x, double _y, Team _team, int _id, int _lvl, Item* _item)
{
    x = _x;
    y = _y;
    team = _team;
    id = _id;
    lvl = _lvl;
    item = _item;

    hpMax = 100 * lvl;
    hp = hpMax;

    attack = 10;
    attackWait = 10;
    actionTime = 0;

    speed = 1;
    range = 10;
    size = 50;
    weight = 1;
    string = "C";
}

double distL2(double x, double y)
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

double mechGap(Mech* mech1, Mech* mech2)
{
    return distL2(mech1->x - mech2->x, mech1->y - mech2->y) - mech1->size
        - mech2->size;
}

void Mech::act(Board board)
{
    if (target.mech == nullptr || target.mech->hp < 0)
    {
        findTarget(board);
        if (target.mech == nullptr)
            return;
    } else
        target.dist = distL2(x - target.mech->x, y - target.mech->y);

    inRange = mechGap(this, target.mech) <= range;

    if (inRange)
    {
        if (actionTime + attackWait <= board.t)
        {
            target.mech->hp -= attack;
            actionTime = board.t;
        }
    } else
    {
        double delta_x = target.mech->x - x;
        double delta_y = target.mech->y - y;
        double norm = distL2(delta_x, delta_y) + SMALL;
        x += delta_x / norm * speed;
        y += delta_y / norm * speed;

        findObstacle(board);
        if (obstacle.mech != nullptr)
            while (mechGap(this, obstacle.mech) < 0)
            {
                double delta_x = obstacle.mech->x - x;
                double delta_y = obstacle.mech->y - y;
                double len =
                    -mechGap(this, obstacle.mech) / (distL2(delta_x, delta_y))
                    + SMALL;
                if ((team == obstacle.mech->team)
                    && (mechGap(obstacle.mech, obstacle.mech->target.mech)
                        > -mechGap(this, obstacle.mech)))
                {
                    double weight_ratio =
                        weight / (weight + obstacle.mech->weight);
                    x -= delta_x * len * (1.0 - weight_ratio);
                    y -= delta_y * len * (1.0 - weight_ratio);
                    obstacle.mech->x += delta_x * len * weight_ratio;
                    obstacle.mech->y += delta_y * len * weight_ratio;
                } else
                {
                    x -= delta_x * len;
                    y -= delta_y * len;
                }

                if (mechGap(this, obstacle.mech) < 0)
                {
                    std::cout << "no success \n";
                }

                findObstacle(board);
            }
        actionTime = board.t;
    }
}

void Mech::findObstacle(Board board)
{
    obstacle = MechRelation();

    for (Mech* mech : board.mechs)
    {
        if (mech != this)
        {
            double dist = distL2(x - mech->x, y - mech->y);
            if ((dist < obstacle.dist))
            {
                obstacle.dist = dist;
                obstacle.mech = mech;
            }
        }
    }
}

void Mech::findTarget(Board board)
{
    target = MechRelation();

    for (Mech* mech : board.mechs)
    {
        if (mech->team != team)
        {
            double dist = distL2(x - mech->x, y - mech->y);
            if ((dist < target.dist))
            {
                target.dist = dist;
                target.mech = mech;
            }
        }
    }
    // std::cout << id << "->" << target.mech->id << "\n";
}

double Mech::calcTargetAngle()
{
    if (target.mech == nullptr)
        return team == TEAM_BLUE ? -90 : 90;

    double delta_x = target.mech->x - x;
    double delta_y = target.mech->y - y;

    double angle = std::atan2(delta_y, delta_x) * 180.0 / M_PI;

    return angle;
}
