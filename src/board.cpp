#include "board.h"

#include "mech.h"
#include "mechs/arclight.h"
#include "mechs/crawler.h"
#include "mechs/meltingpoint.h"
#include "unit.h"

namespace
{
bool checkDeath(Mech* mech)
{
    return !mech->alive;
}
}  // namespace

Board::Board()
{
    units.push_back(new CrawlerUnit(Eigen::Vector2i(33, 0), Team::red, 1, &t, &mechs));
    units.push_back(new CrawlerUnit(Eigen::Vector2i(33, 11), Team::red, 1, &t, &mechs));
    units.push_back(new CrawlerUnit(Eigen::Vector2i(23, 11), Team::red, 1, &t, &mechs));
    units.push_back(new CrawlerUnit(Eigen::Vector2i(44, 11), Team::red, 1, &t, &mechs));

    units.push_back(new ArclightUnit(Eigen::Vector2i(21, 15), Team::red, 2, &t, &mechs));
    units.push_back(new ArclightUnit(Eigen::Vector2i(49, 15), Team::red, 2, &t, &mechs));

    units.push_back(new MeltingPointUnit(Eigen::Vector2i(30, 31), Team::green, 1, &t, &mechs));
    units.push_back(new ArclightUnit(Eigen::Vector2i(28, 33), Team::green, 1, &t, &mechs));

    for (Unit* unit : units)
        mechs.splice(mechs.end(), unit->spawn());
}

void Board::step()
{
    for (Mech* mech : mechs)
        mech->act();

    for (Mech* mech : mechs)
        if (checkDeath(mech))
            mechsDead.push_back(mech);

    mechs.remove_if(checkDeath);

    t++;
}

Board::~Board()
{
    for (Unit* unit : units)
        delete unit;

    for (Mech* mech : mechs)
        delete mech;

    for (Mech* mech : mechsDead)
        delete mech;
}