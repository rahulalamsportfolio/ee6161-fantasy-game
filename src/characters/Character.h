/**
 * @file Character.h
 * @brief Base class for all characters in the game.
 *
 * All player and enemy characters come from this class.
 * Each race must fill in applyDefenceAbility and getRaceName.
 */

#pragma once
#include <string>
#include <vector>
#include <memory>

class Item;

/**
 * @class Character
 * @brief Holds the stats and inventory for one character.
 *
 * This is an abstract class. Use Human, Elf, Dwarf, Hobbit or Orc instead.
 */
class Character
{
public:
    virtual ~Character() = default;

    /**
     * @brief Called when this character successfully defends.
     * @param damage The damage that would have been dealt.
     * @param isDay True if it is daytime.
     * @return The actual damage dealt after the defence ability.
     */
    virtual int applyDefenceAbility(int damage, bool isDay) = 0;

    /**
     * @brief Returns the name of this character's race.
     * @return Race name as a string.
     */
    virtual std::string getRaceName() const = 0;

    /**
     * @brief Called every 5 commands to update day/night stats.
     *        Only Orc overrides this.
     * @param isDay True if it is now daytime.
     */
    virtual void updateTime(bool isDay) { (void)isDay; }

    // --- basic stat getters ---

    /** @return Base attack value. */
    int getBaseAttack() const;

    /** @return Base defence value. */
    int getBaseDefence() const;

    /** @return Current health. */
    int getHealth() const;

    /** @return Max health. */
    int getMaxHealth() const;

    /** @return Max carry weight. */
    int getStrength() const;

    /** @return Gold collected so far. */
    int getGold() const;

    /** @return The character's name. */
    std::string getName() const;

    /** @return True if health is above zero. */
    bool isAlive() const;

    // --- effective stats (base plus item bonuses) ---

    /** @return Attack including any weapon bonus. */
    int getEffectiveAttack() const;

    /** @return Defence including any armour or shield bonus. */
    int getEffectiveDefence() const;

    /** @return Strength including any ring bonus. */
    int getEffectiveStrength() const;

    /** @return Total weight of everything in the inventory. */
    int getTotalWeight() const;

    // --- attack and defence chance ---

    int getAtkNum() const;
    int getAtkDen() const;
    int getDefNum() const;
    int getDefDen() const;

    /**
     * @brief Roll to see if an attack lands.
     * @return True if the attack succeeds.
     */
    bool rollAttack() const;

    /**
     * @brief Roll to see if a defence succeeds.
     * @return True if the defence succeeds.
     */
    bool rollDefence() const;

    // --- inventory ---

    /**
     * @brief Try to pick up an item.
     *
     * Fails if the total weight would go over strength, or if the character
     * already has an item of that category (except rings).
     *
     * @param item The item to pick up.
     * @return True on success.
     */
    bool pickUp(std::unique_ptr<Item> item);

    /**
     * @brief Drop an item from the inventory.
     * @param index Position in the inventory list.
     * @return The dropped item.
     */
    std::unique_ptr<Item> dropItem(int index);

    /** @return Read-only access to the inventory. */
    const std::vector<std::unique_ptr<Item>>& getInventory() const;

    // --- setters ---

    /** @brief Set health directly (capped at maxHealth, min 0). */
    void setHealth(int h);

    /** @brief Add or subtract health. */
    void addHealth(int amount);

    /** @brief Add gold to the total. */
    void addGold(int amount);

    /** @brief Set the character's display name. */
    void setName(const std::string& name);

protected:
    /**
     * @brief Set up a character with given stats.
     *
     * @param name     Display name.
     * @param attack   Base attack.
     * @param atkNum   Attack chance top number.
     * @param atkDen   Attack chance bottom number.
     * @param defence  Base defence.
     * @param defNum   Defence chance top number.
     * @param defDen   Defence chance bottom number.
     * @param health   Starting health.
     * @param strength Max carry weight.
     */
    Character(const std::string& name,
              int attack, int atkNum, int atkDen,
              int defence, int defNum, int defDen,
              int health, int strength);

    int m_attack;
    int m_atkNum, m_atkDen;
    int m_defence;
    int m_defNum, m_defDen;
    int m_health;
    int m_maxHealth;
    int m_strength;
    int m_gold;
    std::string m_name;
    std::vector<std::unique_ptr<Item>> m_inventory;
};
