#include "board.h"

#include "mechs/arclight.h"
#include "mechs/crawler.h"
#include "mechs/meltingpoint.h"

Board::Board(bool check)
{
    if (check)
        std::cout << "Board initialized \n";

    units.push_back(new CrawlerUnit(
        Eigen::Vector2i(72 / 2 - 3, 0), TEAM_RED, 1, &t, &mechs));
    units.push_back(new CrawlerUnit(
        Eigen::Vector2i(72 / 2 - 3, 11), TEAM_RED, 1, &t, &mechs));
    units.push_back(
        new CrawlerUnit(Eigen::Vector2i(21 + 2, 11), TEAM_RED, 1, &t, &mechs));
    units.push_back(new CrawlerUnit(
        Eigen::Vector2i(72 - 21 - 2 - 5, 11), TEAM_RED, 1, &t, &mechs));

    units.push_back(
        new ArclightUnit(Eigen::Vector2i(21, 15), TEAM_RED, 2, &t, &mechs));
    units.push_back(new ArclightUnit(
        Eigen::Vector2i(72 - 21 - 2, 15), TEAM_RED, 2, &t, &mechs));

    units.push_back(new MeltingPointUnit(
        Eigen::Vector2i(34 - 7 + 3, 30 + 1), TEAM_GREEN, 1, &t, &mechs));
    units.push_back(new ArclightUnit(
        Eigen::Vector2i(32 - 7 + 3, 32 + 1), TEAM_GREEN, 1, &t, &mechs));

    for (Unit* unit : units)
        mechsDead.splice(mechsDead.end(), unit->spawn());

    for (Unit* unit : units)
        mechs.splice(mechs.end(), unit->spawn());
}

bool deathCheck(Mech* mech)
{
    return !mech->alive;
}

bool checkDeath(Mech* mech)
{
    return !mech->alive;
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