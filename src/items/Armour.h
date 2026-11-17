/**
 * @file Armour.h
 * @brief An armour item (plate or leather).
 *
 * Plate Armour:   weight 40, +10 defence, -5 attack.
 * Leather Armour: weight 20, +5 defence.
 */

#pragma once
#include "Item.h"

/**
 * @class Armour
 * @brief Adds defence and may reduce attack.
 */
class Armour : public Item
{
public:
    /**
     * @brief Create an armour item.
     * @param name          Name.
     * @param weight        Weight.
     * @param defenceBonus  Defence added.
     * @param attackPenalty Attack reduced (pass positive number).
     */
    Armour(const std::string& name, int weight, int defenceBonus, int attackPenalty);

    std::string getName()       const override;
    ItemCategory getCategory()  const override;
    int getWeight()             const override;
    int getAttackBonus()        const override;
    int getDefenceBonus()       const override;

private:
    std::string m_name;
    int m_weight, m_defenceBonus, m_attackPenalty;
};
