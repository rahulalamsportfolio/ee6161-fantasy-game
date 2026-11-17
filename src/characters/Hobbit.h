/**
 * @file Hobbit.h
 * @brief Hobbit race character.
 */

#pragma once
#include "Character.h"

/**
 * @class Hobbit
 * @brief A hobbit character.
 */
class Hobbit : public Character
{
public:
    explicit Hobbit(const std::string& name);
    int applyDefenceAbility(int damage, bool isDay) override;
    std::string getRaceName() const override;
};
