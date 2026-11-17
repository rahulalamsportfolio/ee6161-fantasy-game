/**
 * @file Ring.cpp
 * @brief Implementation of the Ring item.
 */

#include "Ring.h"

Ring::Ring(const std::string& name, int strengthBonus, int healthBonus)
    : m_name(name), m_strengthBonus(strengthBonus), m_healthBonus(healthBonus) {}

std::string  Ring::getName()          const { return m_name; }
ItemCategory Ring::getCategory()      const { return ItemCategory::Ring; }
int          Ring::getWeight()        const { return 1; }
int          Ring::getStrengthBonus() const { return m_strengthBonus; }
int          Ring::getHealthBonus()   const { return m_healthBonus; }
