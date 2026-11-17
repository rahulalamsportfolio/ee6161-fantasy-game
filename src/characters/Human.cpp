/**
 * @file Human.cpp
 * @brief Implementation of the Human race.
 */

#include "Human.h"
#include <cstdlib>

Human::Human(const std::string& name)
    : Character(name, 30,2,3, 20,1,2, 60, 100)
{}

int Human::applyDefenceAbility(int damage, bool isDay)
{
    (void)damage; (void)isDay;
    return 0;
}

std::string Human::getRaceName() const
{
    return "Human";
}
