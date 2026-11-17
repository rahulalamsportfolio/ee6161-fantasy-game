/**
 * @file Dwarf.h
 * @brief Dwarf race character.
 */

#pragma once
#include "Character.h"

/**
 * @class Dwarf
 * @brief A dwarf character.
 */
class Dwarf : public Character
{
public:
    explicit Dwarf(const std::string& name);
    int applyDefenceAbility(int damage, bool isDay) override;
    std::string getRaceName() const override;
};
