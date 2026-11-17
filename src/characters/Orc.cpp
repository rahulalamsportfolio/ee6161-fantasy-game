/**
 * @file Orc.cpp
 * @brief Implementation of the Orc race.
 */

#include "Orc.h"

Orc::Orc(const std::string& name)
    : Character(name, 25,1,4, 10,1,4, 50, 130)
{}

void Orc::updateTime(bool isDay)
{
    if (isDay)
    {
        m_attack  = 25; m_atkNum = 1; m_atkDen = 4;
        m_defence = 10; m_defNum = 1; m_defDen = 4;
    }
    else
    {
        m_attack  = 45; m_atkNum = 1; m_atkDen = 1;
        m_defence = 25; m_defNum = 1; m_defDen = 2;
    }
}

int Orc::applyDefenceAbility(int damage, bool isDay)
{
    if (isDay)
        return damage / 4;   // 1/4 of adjusted damage
    else
    {
        addHealth(1);        // night: heal instead
        return 0;
    }
}

std::string Orc::getRaceName() const
{
    return "Orc";
}
