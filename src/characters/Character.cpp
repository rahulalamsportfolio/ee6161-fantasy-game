/**
 * @file Character.cpp
 * @brief Implementation of the Character base class.
 */

#include "Character.h"
#include "items/Item.h"
#include <cstdlib>
#include <algorithm>

// --- constructor ---

Character::Character(const std::string& name,
                     int attack, int atkNum, int atkDen,
                     int defence, int defNum, int defDen,
                     int health, int strength)
    : m_name(name),
      m_attack(attack), m_atkNum(atkNum), m_atkDen(atkDen),
      m_defence(defence), m_defNum(defNum), m_defDen(defDen),
      m_health(health), m_maxHealth(health),
      m_strength(strength), m_gold(0)
{
}

// --- basic getters ---

int Character::getBaseAttack()  const { return m_attack; }
int Character::getBaseDefence() const { return m_defence; }
int Character::getHealth()      const { return m_health; }
int Character::getMaxHealth()   const { return m_maxHealth; }
int Character::getStrength()    const { return m_strength; }
int Character::getGold()        const { return m_gold; }
std::string Character::getName() const { return m_name; }
bool Character::isAlive()       const { return m_health > 0; }

int Character::getAtkNum() const { return m_atkNum; }
int Character::getAtkDen() const { return m_atkDen; }
int Character::getDefNum() const { return m_defNum; }
int Character::getDefDen() const { return m_defDen; }

// --- effective stats (base plus everything in inventory) ---

int Character::getEffectiveAttack() const
{
    int total = m_attack;
    for (const auto& item : m_inventory)
        total += item->getAttackBonus();
    return total;
}

int Character::getEffectiveDefence() const
{
    int total = m_defence;
    for (const auto& item : m_inventory)
        total += item->getDefenceBonus();
    return total;
}

int Character::getEffectiveStrength() const
{
    int total = m_strength;
    for (const auto& item : m_inventory)
        total += item->getStrengthBonus();
    return total;
}

int Character::getTotalWeight() const
{
    int total = 0;
    for (const auto& item : m_inventory)
        total += item->getWeight();
    return total;
}

// --- dice rolls ---

bool Character::rollAttack() const
{
    // e.g. 2/3 chance: roll 1..3, succeed if roll <= 2
    int roll = (std::rand() % m_atkDen) + 1;
    return roll <= m_atkNum;
}

bool Character::rollDefence() const
{
    int roll = (std::rand() % m_defDen) + 1;
    return roll <= m_defNum;
}

// --- inventory ---

bool Character::pickUp(std::unique_ptr<Item> item)
{
    // check weight
    if (getTotalWeight() + item->getWeight() > getEffectiveStrength())
        return false;

    // rings can stack, all other categories are limited to one each
    if (item->getCategory() != ItemCategory::Ring)
    {
        for (const auto& held : m_inventory)
        {
            if (held->getCategory() == item->getCategory())
                return false;
        }
    }

    // ring of health gives an instant health boost
    if (item->getCategory() == ItemCategory::Ring && item->getHealthBonus() > 0)
        addHealth(item->getHealthBonus());

    m_inventory.push_back(std::move(item));
    return true;
}

std::unique_ptr<Item> Character::dropItem(int index)
{
    if (index < 0 || index >= static_cast<int>(m_inventory.size()))
        return nullptr;

    auto dropped = std::move(m_inventory[index]);
    m_inventory.erase(m_inventory.begin() + index);
    return dropped;
}

const std::vector<std::unique_ptr<Item>>& Character::getInventory() const
{
    return m_inventory;
}

// --- setters ---

void Character::setHealth(int h)
{
    m_health = std::max(0, std::min(h, m_maxHealth));
}

void Character::addHealth(int amount)
{
    setHealth(m_health + amount);
}

void Character::addGold(int amount)
{
    m_gold += amount;
}

void Character::setName(const std::string& name)
{
    m_name = name;
}
