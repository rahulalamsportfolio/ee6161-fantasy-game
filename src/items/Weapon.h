/**
 * @file Weapon.h
 * @brief A weapon item (sword or dagger).
 *
 * Sword:  weight 10, +10 attack.
 * Dagger: weight 5,  +5 attack.
 */

#pragma once
#include "Item.h"

/**
 * @class Weapon
 * @brief Adds to attack while carried.
 */
class Weapon : public Item
{
public:
    /**
     * @brief Create a weapon.
     * @param name   Name (e.g. "Sword").
     * @param weight How heavy it is.
     * @param bonus  Attack bonus.
     */
    Weapon(const std::string& name, int weight, int bonus);

    std::string getName()       const override;
    ItemCategory getCategory()  const override;
    int getWeight()             const override;
    int getAttackBonus()        const override;

private:
    std::string m_name;
    int m_weight;
    int m_bonus;
};
