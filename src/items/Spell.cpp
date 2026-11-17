/**
 * @file Spell.cpp
 * @brief Implementation of the Spell item.
 */

#include "Spell.h"

Spell::Spell(const std::string& name, int weight, int damage)
    : m_name(name), m_weight(weight), m_damage(damage) {}

std::string  Spell::getName()      const { return m_name; }
ItemCategory Spell::getCategory()  const { return ItemCategory::Spell; }
int          Spell::getWeight()    const { return m_weight; }
bool         Spell::isConsumable() const { return true; }
int          Spell::getDamage()    const { return m_damage; }
