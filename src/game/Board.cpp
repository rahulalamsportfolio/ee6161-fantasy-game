/**
 * @file Board.cpp
 * @brief Implementation of Board.
 */

#include "Board.h"
#include "characters/Human.h"
#include "characters/Elf.h"
#include "characters/Dwarf.h"
#include "characters/Hobbit.h"
#include "characters/Orc.h"
#include "items/Weapon.h"
#include "items/Armour.h"
#include "items/Shield.h"
#include "items/Ring.h"
#include "items/Potion.h"
#include "items/Spell.h"
#include <cstdlib>
#include <ctime>

Board::Board(int width, int height) : m_width(width), m_height(height)
{
    // build the grid - each cell gets a fresh Square
    m_grid.resize(height);
    for (int y = 0; y < height; ++y)
    {
        m_grid[y].resize(width);
        for (int x = 0; x < width; ++x)
            m_grid[y][x] = std::make_unique<Square>();
    }
}

int Board::getWidth()  const { return m_width; }
int Board::getHeight() const { return m_height; }

Square* Board::getSquare(int x, int y) const
{
    if (!isValid(x, y)) return nullptr;
    return m_grid[y][x].get();
}

bool Board::isValid(int x, int y) const
{
    return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

void Board::initialise()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // helper lambda to pick a random enemy name
    auto randName = [](const std::string& race) -> std::string {
        static const char* names[] = {"Ash","Stone","Flame","Mire","Dusk"};
        return race + " " + names[std::rand() % 5];
    };

    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            // skip starting square (0,0)
            if (x == 0 && y == 0) continue;

            int roll = std::rand() % 10;

            if (roll < 3)
            {
                // 30% chance: place an enemy
                int r = std::rand() % 5;
                std::unique_ptr<Character> enemy;
                std::string name = randName({"Human","Elf","Dwarf","Hobbit","Orc"}[r]);
                switch (r)
                {
                    case 0: enemy = std::make_unique<Human>(name);  break;
                    case 1: enemy = std::make_unique<Elf>(name);    break;
                    case 2: enemy = std::make_unique<Dwarf>(name);  break;
                    case 3: enemy = std::make_unique<Hobbit>(name); break;
                    default: enemy = std::make_unique<Orc>(name);   break;
                }
                m_grid[y][x]->placeEnemy(std::move(enemy));
            }
            else if (roll < 6)
            {
                // 30% chance: place a random item
                int r = std::rand() % 8;
                std::unique_ptr<Item> item;
                switch (r)
                {
                    case 0: item = std::make_unique<Weapon>("Sword",  10, 10); break;
                    case 1: item = std::make_unique<Weapon>("Dagger",  5,  5); break;
                    case 2: item = std::make_unique<Armour>("Plate Armour",   40, 10, 5); break;
                    case 3: item = std::make_unique<Armour>("Leather Armour", 20,  5, 0); break;
                    case 4: item = std::make_unique<Shield>("Large Shield", 25, 10, 5); break;
                    case 5: item = std::make_unique<Shield>("Small Shield", 15,  5, 0); break;
                    case 6: item = std::make_unique<Potion>("Potion of Health", 20, 0); break;
                    default: item = std::make_unique<Ring>("Ring of Strength", 10, 0); break;
                }
                m_grid[y][x]->placeItem(std::move(item));
            }
            // 40% chance: square stays empty
        }
    }
}
