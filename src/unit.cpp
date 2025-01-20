#include "unit.h"

#include "item.h"
#include "mech.h"

Unit::Unit(Eigen::Vector2i _position,
           Team _team,
           int _lvl,
           int* _t,
           std::list<Mech*>* _mechs)
    : position(_position)
    , team(_team)
    , lvl(_lvl)
    , t(_t)
    , mechs(_mechs)
{
    item = new Item();
}

std::list<Mech*> Unit::spawn()
{
    Eigen::Vector2i count(getCount(), 1);
    while (count.x() > 10)
        count += Eigen::Vector2i(-10, 1);
    if (count.x() * count.y() != getCount())
        throw std::runtime_error(
            "Unit count can't be divided into rows and columns");

    if (transposed)
        std::swap(count.x(), count.y());

    Eigen::Vector2d scale =
        getSize().cast<double>().array() / count.cast<double>().array();

    std::list<Mech*> mechsNew;
    for (int x = 0; x < count.x(); x++)
        for (int y = 0; y < count.y(); y++)
        {
            Eigen::Vector2d mechPosition = position.cast<double>().array()
                + (Eigen::Vector2d(x, y).array() + 0.5) * scale.array();
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
        return Eigen::Vector2i(getBaseSize().y(), getBaseSize().x());
    else
        return getBaseSize();
}