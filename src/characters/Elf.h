/**
 * @file Elf.h
 * @brief Elf race character.
 */

#pragma once
#include "Character.h"

/**
 * @class Elf
 * @brief A elf character.
 */
class Elf : public Character
{
public:
    explicit Elf(const std::string& name);
    int applyDefenceAbility(int damage, bool isDay) override;
    std::string getRaceName() const override;
};
