/**
 * @file Square.cpp
 * @brief Implementation of Square.
 */

#include "Square.h"

Square::Square() {}

bool Square::hasEnemy() const { return m_enemy != nullptr; }
bool Square::hasItem()  const { return m_item  != nullptr; }
bool Square::isEmpty()  const { return !hasEnemy() && !hasItem(); }

Character* Square::getEnemy() const { return m_enemy.get(); }
Item*      Square::getItem()  const { return m_item.get();  }

void Square::placeEnemy(std::unique_ptr<Character> enemy) { m_enemy = std::move(enemy); }
void Square::placeItem(std::unique_ptr<Item> item)        { m_item  = std::move(item);  }

std::unique_ptr<Character> Square::removeEnemy() { return std::move(m_enemy); }
std::unique_ptr<Item>      Square::removeItem()  { return std::move(m_item);  }
