#include "unit.h"

#include "item.h"
#include "mech.h"

Unit::Unit(
    Eigen::Vector2i positionArg, Team teamArg, int lvlArg, int* tArg, std::list<Mech*>* mechsArg)
    : position(std::move(positionArg))
    , team(teamArg)
    , lvl(lvlArg)
    , t(tArg)
    , mechs(mechsArg)
    , item(new Item())
{
}

Unit::~Unit()
{
    delete item;
}

std::list<Mech*> Unit::spawn()
{
    Eigen::Vector2i count(getCount(), 1);
    while (count.x() > 10)
        count += Eigen::Vector2i(-10, 1);
    if (count.x() * count.y() != getCount())
        throw std::runtime_error("Unit count can't be divided into rows and columns");

    if (transposed)
        std::swap(count.x(), count.y());

    Eigen::Vector2d scale = getSize().cast<double>().array() / count.cast<double>().array();

    std::list<Mech*> mechsNew;
    for (int xPos = 0; xPos < count.x(); xPos++)
        for (int yPos = 0; yPos < count.y(); yPos++)
        {
            const Eigen::Vector2d mechPosition = position.cast<double>().array()
                + (Eigen::Vector2d(xPos, yPos).array() + 0.5) * scale.array();
            mechsNew.push_back(makeMech(mechPosition));
        }

    return mechsNew;
}

void Unit::lvlUp()
{
    lvl += 1;
}

Eigen::Vector2i Unit::getSize()
{
    if (transposed)
        return {getBaseSize().y(), getBaseSize().x()};
    return getBaseSize();
}