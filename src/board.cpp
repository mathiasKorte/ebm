#include <iostream>

#include "board.h"

#include "item.h"
#include "mechs.h"

Board::Board(bool check)
{
    if (check)
        std::cout << "Board initialized \n";

    Item* item = new Item();

    Crawler* c1 = new Crawler(900, 200, TEAM_RED, 1, 1, item);
    Crawler* c2 = new Crawler(900, 600, TEAM_RED, 2, 1, item);
    Crawler* c3 = new Crawler(901, 601, TEAM_RED, 3, 2, item);
    Crawler* c4 = new Crawler(100, 500, TEAM_BLUE, 4, 1, item);
    Crawler* c5 = new Crawler(101, 500, TEAM_BLUE, 5, 1, item);
    Crawler* c6 = new Crawler(100, 501, TEAM_BLUE, 6, 2, item);
    Crawler* c7 = new Crawler(101, 501, TEAM_BLUE, 7, 3, item);

    mechs.push_back(c1);
    mechs.push_back(c2);
    mechs.push_back(c3);
    mechs.push_back(c4);
    mechs.push_back(c5);
    mechs.push_back(c6);
    mechs.push_back(c7);

    for (Mech* mech : mechs)
        mech->findTarget(*this);
}

bool deathCheck(Mech* mech)
{
    return mech->hp <= 0;
}

void Board::step()
{
    if (t % 1000 == 0)
        for (Mech* mech : mechs)
            if (!mech->inRange)
                mech->findTarget(*this);

    for (Mech* mech : mechs)
        mech->act(*this);

    mechs.remove_if(deathCheck);

    t++;
}