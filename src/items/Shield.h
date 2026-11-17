/**
 * @file Shield.h
 * @brief A shield item (large or small).
 *
 * Large Shield: weight 25, +10 defence, -5 attack.
 * Small Shield: weight 15, +5 defence.
 */

#pragma once
#include "Item.h"

/**
 * @class Shield
 * @brief Adds defence and may reduce attack.
 */
class Shield : public Item
{
public:
    Shield(const std::string& name, int weight, int defenceBonus, int attackPenalty);

    std::string getName()       const override;
    ItemCategory getCategory()  const override;
    int getWeight()             const override;
    int getAttackBonus()        const override;
    int getDefenceBonus()       const override;

private:
    std::string m_name;
    int m_weight, m_defenceBonus, m_attackPenalty;
};
