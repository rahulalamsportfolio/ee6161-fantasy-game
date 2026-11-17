/**
 * @file Spell.h
 * @brief A spell item (fireball or lightning).
 *
 * Spell of Fireball:  weight 5, deals 20 damage (ignores defence).
 * Spell of Lightning: weight 3, deals 10 damage.
 */

#pragma once
#include "Item.h"

/**
 * @class Spell
 * @brief A consumable spell that damages an enemy directly.
 */
class Spell : public Item
{
public:
    /**
     * @brief Create a spell.
     * @param name    Name.
     * @param weight  Weight.
     * @param damage  How much damage it deals.
     */
    Spell(const std::string& name, int weight, int damage);

    std::string getName()      const override;
    ItemCategory getCategory() const override;
    int getWeight()            const override;
    bool isConsumable()        const override;

    /** @return How much damage this spell deals. */
    int getDamage() const;

    // Note: spells target an enemy, so they are cast via Game::castSpell
    // rather than through the standard use() method.

private:
    std::string m_name;
    int m_weight, m_damage;
};
