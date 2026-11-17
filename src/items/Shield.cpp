/**
 * @file Shield.cpp
 * @brief Implementation of the Shield item.
 */

#include "Shield.h"

Shield::Shield(const std::string& name, int weight, int defenceBonus, int attackPenalty)
    : m_name(name), m_weight(weight), m_defenceBonus(defenceBonus), m_attackPenalty(attackPenalty) {}

std::string  Shield::getName()         const { return m_name; }
ItemCategory Shield::getCategory()     const { return ItemCategory::Shield; }
int          Shield::getWeight()       const { return m_weight; }
int          Shield::getAttackBonus()  const { return -m_attackPenalty; }
int          Shield::getDefenceBonus() const { return m_defenceBonus; }
