/**
 * @file Elf.cpp
 * @brief Implementation of the Elf race.
 */

#include "Elf.h"
#include <cstdlib>

Elf::Elf(const std::string& name)
    : Character(name, 40,1,1, 10,1,4, 40, 70)
{}

int Elf::applyDefenceAbility(int damage, bool isDay)
{
    (void)damage; (void)isDay;
    addHealth(1); return 0;
}

std::string Elf::getRaceName() const
{
    return "Elf";
}
