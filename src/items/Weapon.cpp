/**
 * @file Weapon.cpp
 * @brief Implementation of the Weapon item.
 */

#include "Weapon.h"

Weapon::Weapon(const std::string& name, int weight, int bonus)
    : m_name(name), m_weight(weight), m_bonus(bonus) {}

std::string  Weapon::getName()      const { return m_name; }
ItemCategory Weapon::getCategory()  const { return ItemCategory::Weapon; }
int          Weapon::getWeight()    const { return m_weight; }
int          Weapon::getAttackBonus() const { return m_bonus; }
