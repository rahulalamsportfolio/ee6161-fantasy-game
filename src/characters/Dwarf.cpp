/**
 * @file Dwarf.cpp
 * @brief Implementation of the Dwarf race.
 */

#include "Dwarf.h"
#include <cstdlib>

Dwarf::Dwarf(const std::string& name)
    : Character(name, 30,2,3, 20,2,3, 50, 130)
{}

int Dwarf::applyDefenceAbility(int damage, bool isDay)
{
    (void)damage; (void)isDay;
    return 0;
}

std::string Dwarf::getRaceName() const
{
    return "Dwarf";
}
