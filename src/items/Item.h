/**
 * @file Item.h
 * @brief Base class for all items in the game.
 *
 * Items sit on board squares and can be picked up by characters.
 * Some items add bonuses while carried. Others are used once (potions, spells).
 */

#pragma once
#include <string>

class Character;

/**
 * @enum ItemCategory
 * @brief The type of an item.
 *
 * A character can carry one item per category, except Ring
 * (they can carry as many rings as their strength allows).
 */
enum class ItemCategory { Weapon, Armour, Shield, Ring, Potion, Spell };

/**
 * @class Item
 * @brief Abstract base class for all game items.
 */
class Item
{
public:
    virtual ~Item() = default;

    /** @return The item name. */
    virtual std::string getName() const = 0;

    /** @return Which category this item belongs to. */
    virtual ItemCategory getCategory() const = 0;

    /** @return How much the item weighs. */
    virtual int getWeight() const = 0;

    // bonus getters - return 0 by default

    /** @return Attack bonus while carried (can be negative). */
    virtual int getAttackBonus()   const { return 0; }

    /** @return Defence bonus while carried. */
    virtual int getDefenceBonus()  const { return 0; }

    /** @return Strength bonus while carried. */
    virtual int getStrengthBonus() const { return 0; }

    /** @return Health bonus applied at pickup. */
    virtual int getHealthBonus()   const { return 0; }

    /** @return True for potions and spells (used once then removed). */
    virtual bool isConsumable() const { return false; }

    /**
     * @brief Use this item on a character. Only for consumables.
     * @param ch The character using the item.
     */
    virtual void use(Character& ch) { (void)ch; }
};
