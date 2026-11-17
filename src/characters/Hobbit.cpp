/**
 * @file Hobbit.cpp
 * @brief Implementation of the Hobbit race.
 */

#include "Hobbit.h"
#include <cstdlib>

Hobbit::Hobbit(const std::string& name)
    : Character(name, 25,1,3, 20,2,3, 70, 85)
{}

int Hobbit::applyDefenceAbility(int damage, bool isDay)
{
    (void)damage; (void)isDay;
    return std::rand() % 6;
}

std::string Hobbit::getRaceName() const
{
    return "Hobbit";
}
