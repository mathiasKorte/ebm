#pragma once
#include <limits>
#include <string>

#include "board.h"
#include "item.h"

struct MechRelation
{
    Mech* mech = nullptr;
    double dist = std::numeric_limits<double>::max();
    double damage = 0;
};

class Mech
{
  public:
    double x;
    double y;
    Team team;
    double hp;
    double hpMax;
    double speed;
    double range;
    double weight;
    double size;
    double attack;
    u_int64_t attackWait;
    u_int64_t actionTime;
    MechRelation target;
    MechRelation obstacle;
    int id;
    bool inRange = false;
    int lvl;
    std::string string;
    Item* item;

    virtual ~Mech() = default;
    // virtual void act(Board board) = 0;

    void act(Board board);
    void findTarget(Board board);
    void findObstacle(Board board);
    double calcTargetAngle();
};

class Crawler : public Mech
{
  public:
    Crawler(double _x, double _y, Team _team, int _id, int _lvl, Item* _item);

    // void act(Board board) override;
};