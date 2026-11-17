/**
 * @file Orc.h
 * @brief Orc race character.
 *
 * Day:   Attack 25 (1/4), Defence 10 (1/4), Health 50, Strength 130.
 * Night: Attack 45 (1/1), Defence 25 (1/2), Health 50, Strength 130.
 * Special (day):   defence reduces damage to 1/4 of adjusted damage.
 * Special (night): defence restores 1 health.
 */

#pragma once
#include "Character.h"

/**
 * @class Orc
 * @brief An orc. Gets much stronger at night.
 */
class Orc : public Character
{
public:
    explicit Orc(const std::string& name);
    void updateTime(bool isDay) override;
    int applyDefenceAbility(int damage, bool isDay) override;
    std::string getRaceName() const override;
};
