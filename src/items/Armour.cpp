/**
 * @file Armour.cpp
 * @brief Implementation of the Armour item.
 */

#include "Armour.h"

Armour::Armour(const std::string& name, int weight, int defenceBonus, int attackPenalty)
    : m_name(name), m_weight(weight), m_defenceBonus(defenceBonus), m_attackPenalty(attackPenalty) {}

std::string  Armour::getName()       const { return m_name; }
ItemCategory Armour::getCategory()   const { return ItemCategory::Armour; }
int          Armour::getWeight()     const { return m_weight; }
int          Armour::getAttackBonus()  const { return -m_attackPenalty; }
int          Armour::getDefenceBonus() const { return m_defenceBonus; }
