/**
 * @file Square.h
 * @brief One square on the game board.
 *
 * A square can hold one enemy or one item, or be empty.
 */

#pragma once
#include <memory>

class Character;
class Item;

/**
 * @class Square
 * @brief Holds whatever is on one tile of the board.
 */
class Square
{
public:
    Square();

    bool hasEnemy() const;
    bool hasItem()  const;
    bool isEmpty()  const;

    /** @return Pointer to the enemy on this square, or nullptr. */
    Character* getEnemy() const;

    /** @return Pointer to the item on this square, or nullptr. */
    Item* getItem() const;

    /** @brief Place an enemy here. */
    void placeEnemy(std::unique_ptr<Character> enemy);

    /** @brief Place an item here. */
    void placeItem(std::unique_ptr<Item> item);

    /** @brief Remove and return the enemy. */
    std::unique_ptr<Character> removeEnemy();

    /** @brief Remove and return the item. */
    std::unique_ptr<Item> removeItem();

private:
    std::unique_ptr<Character> m_enemy;
    std::unique_ptr<Item>      m_item;
};
