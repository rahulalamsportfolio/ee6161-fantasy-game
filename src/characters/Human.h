/**
 * @file Human.h
 * @brief Human race character.
 */

#pragma once
#include "Character.h"

/**
 * @class Human
 * @brief A human character.
 */
class Human : public Character
{
public:
    explicit Human(const std::string& name);
    int applyDefenceAbility(int damage, bool isDay) override;
    std::string getRaceName() const override;
};
