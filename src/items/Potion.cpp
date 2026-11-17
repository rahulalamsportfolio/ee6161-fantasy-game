/**
 * @file Potion.cpp
 * @brief Implementation of the Potion item.
 */

#include "Potion.h"
#include "characters/Character.h"

Potion::Potion(const std::string& name, int healthRestore, int strengthBoost)
    : m_name(name), m_healthRestore(healthRestore), m_strengthBoost(strengthBoost) {}

std::string  Potion::getName()      const { return m_name; }
ItemCategory Potion::getCategory()  const { return ItemCategory::Potion; }
int          Potion::getWeight()    const { return 5; }
bool         Potion::isConsumable() const { return true; }

void Potion::use(Character& ch)
{
    if (m_healthRestore > 0)
        ch.addHealth(m_healthRestore);
    // TODO: temporary strength boost (needs a timer system)
    (void)m_strengthBoost;
}
