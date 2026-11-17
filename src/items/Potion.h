/**
 * @file Potion.h
 * @brief A potion item (health or strength).
 *
 * Potion of Health:   weight 5, restores 20 health when drunk.
 * Potion of Strength: weight 5, adds 10 strength temporarily when drunk.
 */

#pragma once
#include "Item.h"

/**
 * @class Potion
 * @brief A consumable that restores health or strength.
 */
class Potion : public Item
{
public:
    /**
     * @brief Create a potion.
     * @param name         Name.
     * @param healthRestore  How much health it restores (0 if none).
     * @param strengthBoost  How much strength it adds (0 if none).
     */
    Potion(const std::string& name, int healthRestore, int strengthBoost);

    std::string getName()      const override;
    ItemCategory getCategory() const override;
    int getWeight()            const override;
    bool isConsumable()        const override;
    void use(Character& ch)          override;

private:
    std::string m_name;
    int m_healthRestore, m_strengthBoost;
};
