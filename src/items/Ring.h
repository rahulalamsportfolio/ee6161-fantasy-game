/**
 * @file Ring.h
 * @brief A ring item (ring of strength or ring of health).
 *
 * Characters can carry more than one ring.
 * Ring of Strength: weight 1, +10 strength while carried.
 * Ring of Health:   weight 1, +10 health when picked up.
 */

#pragma once
#include "Item.h"

/**
 * @class Ring
 * @brief Gives a strength or health bonus.
 */
class Ring : public Item
{
public:
    /**
     * @brief Create a ring.
     * @param name           Name (e.g. "Ring of Strength").
     * @param strengthBonus  Strength added while carried (0 if none).
     * @param healthBonus    Health added at pickup (0 if none).
     */
    Ring(const std::string& name, int strengthBonus, int healthBonus);

    std::string getName()        const override;
    ItemCategory getCategory()   const override;
    int getWeight()              const override;
    int getStrengthBonus()       const override;
    int getHealthBonus()         const override;

private:
    std::string m_name;
    int m_strengthBonus, m_healthBonus;
};
