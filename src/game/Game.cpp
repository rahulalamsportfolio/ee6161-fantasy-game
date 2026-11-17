/**
 * @file Game.cpp
 * @brief Implementation of Game.
 */

#include "Game.h"
#include "characters/Human.h"
#include "characters/Elf.h"
#include "characters/Dwarf.h"
#include "characters/Hobbit.h"
#include "characters/Orc.h"
#include "items/Spell.h"
#include "items/Potion.h"
#include <cstdlib>

Game::Game()
    : m_playerX(0), m_playerY(0), m_commandCount(0),
      m_isDay(true), m_running(false), m_gameOver(false)
{}

void Game::newGame(int width, int height,
                   const std::string& playerName, int raceChoice)
{
    m_board = std::make_unique<Board>(width, height);
    m_board->initialise();

    // create the player character based on race choice
    switch (raceChoice)
    {
        case 1:  m_player = std::make_unique<Elf>(playerName);    break;
        case 2:  m_player = std::make_unique<Dwarf>(playerName);  break;
        case 3:  m_player = std::make_unique<Hobbit>(playerName); break;
        case 4:  m_player = std::make_unique<Orc>(playerName);    break;
        default: m_player = std::make_unique<Human>(playerName);  break;
    }

    m_playerX = 0; m_playerY = 0;
    m_commandCount = 0;
    m_isDay = true;
    m_running = true;
    m_gameOver = false;
    m_lastMessage = "Game started. Good luck!";
}

void Game::processCommand(char cmd)
{
    if (!m_running) return;

    // convert to lowercase
    cmd = static_cast<char>(std::tolower(cmd));

    switch (cmd)
    {
        case 'n': movePlayer( 0, -1); break;
        case 's': movePlayer( 0,  1); break;
        case 'e': movePlayer( 1,  0); break;
        case 'w': movePlayer(-1,  0); break;
        case 'p': pickUpItem();        break;
        case 'd': dropItem();          break;
        case 'a': attackEnemy();       break;
        case 'c': castSpell();         break;
        case 'k': drinkPotion();       break;
        case 'q': m_running = false;   break;
        default: m_lastMessage = "Unknown command."; return;
    }

    // count the command and check if time should change
    if (cmd != 'q')
    {
        ++m_commandCount;
        advanceTime();
    }

    // check if player has died
    if (!m_player->isAlive())
    {
        m_running  = false;
        m_gameOver = true;
        m_lastMessage += " You have been defeated! Gold: "
                       + std::to_string(m_player->getGold());
    }
}

void Game::movePlayer(int dx, int dy)
{
    int nx = m_playerX + dx;
    int ny = m_playerY + dy;

    if (!m_board->isValid(nx, ny))
    {
        m_lastMessage = "You cannot go that way.";
        return;
    }

    m_playerX = nx;
    m_playerY = ny;
    Square* sq = m_board->getSquare(nx, ny);

    if (sq->hasEnemy())
        m_lastMessage = "There is an enemy here: " + sq->getEnemy()->getName();
    else if (sq->hasItem())
        m_lastMessage = "There is an item here: " + sq->getItem()->getName();
    else
        m_lastMessage = "The square is empty.";
}

void Game::attackEnemy()
{
    Square* sq = m_board->getSquare(m_playerX, m_playerY);
    if (!sq->hasEnemy())
    {
        m_lastMessage = "No enemy here to attack.";
        return;
    }

    Character* enemy = sq->getEnemy();
    std::string log = resolveAttack(*m_player, *enemy);

    // enemy counterattacks if still alive
    if (enemy->isAlive())
        log += " | " + resolveAttack(*enemy, *m_player);
    else
    {
        // enemy defeated - award gold equal to enemy defence value
        int gold = enemy->getEffectiveDefence();
        m_player->addGold(gold);
        log += " Enemy defeated! +" + std::to_string(gold) + " gold.";
        sq->removeEnemy();
    }

    m_lastMessage = log;
}

std::string Game::resolveAttack(Character& attacker, Character& defender)
{
    std::string msg = attacker.getName() + " attacks " + defender.getName() + ". ";

    // step 1: does the attack land?
    if (!attacker.rollAttack())
        return msg + "Attack missed.";

    msg += "Hit! ";

    // step 2: does the defender block?
    if (defender.rollDefence())
    {
        int adjustedDamage = attacker.getEffectiveAttack() - defender.getEffectiveDefence();
        if (adjustedDamage < 0) adjustedDamage = 0;
        int actualDamage = defender.applyDefenceAbility(adjustedDamage, m_isDay);
        defender.addHealth(-actualDamage);
        msg += "Defended! Took " + std::to_string(actualDamage) + " damage.";
    }
    else
    {
        // defence failed - full adjusted damage
        int damage = attacker.getEffectiveAttack() - defender.getEffectiveDefence();
        if (damage < 0) damage = 0;
        defender.addHealth(-damage);
        msg += "No defence! Took " + std::to_string(damage) + " damage.";
    }

    return msg;
}

void Game::pickUpItem()
{
    Square* sq = m_board->getSquare(m_playerX, m_playerY);
    if (!sq->hasItem())
    {
        m_lastMessage = "No item here.";
        return;
    }

    std::string itemName = sq->getItem()->getName();
    auto item = sq->removeItem();

    if (m_player->pickUp(std::move(item)))
        m_lastMessage = "Picked up " + itemName + ".";
    else
    {
        // put it back if pickup failed
        sq->placeItem(std::move(item));
        m_lastMessage = "Cannot pick up " + itemName + " (too heavy or already have one).";
    }
}

void Game::dropItem()
{
    // TODO: ask the player which item to drop via the UI
    if (m_player->getInventory().empty())
    {
        m_lastMessage = "Your inventory is empty.";
        return;
    }
    // drop the first item for now - replace with UI selection
    auto dropped = m_player->dropItem(0);
    Square* sq = m_board->getSquare(m_playerX, m_playerY);
    std::string name = dropped->getName();
    sq->placeItem(std::move(dropped));
    m_lastMessage = "Dropped " + name + ".";
}

void Game::castSpell()
{
    // find first spell in inventory
    const auto& inv = m_player->getInventory();
    int spellIdx = -1;
    for (int i = 0; i < static_cast<int>(inv.size()); ++i)
    {
        if (inv[i]->getCategory() == ItemCategory::Spell)
        { spellIdx = i; break; }
    }

    if (spellIdx < 0) { m_lastMessage = "No spell in inventory."; return; }

    Square* sq = m_board->getSquare(m_playerX, m_playerY);
    if (!sq->hasEnemy()) { m_lastMessage = "No enemy here."; return; }

    Spell* spell = static_cast<Spell*>(inv[spellIdx].get());
    Character* enemy = sq->getEnemy();
    int damage = spell->getDamage();
    enemy->addHealth(-damage);
    m_lastMessage = "Cast " + spell->getName() + " for " + std::to_string(damage) + " damage!";

    m_player->dropItem(spellIdx); // consume the spell

    if (!enemy->isAlive())
    {
        int gold = enemy->getEffectiveDefence();
        m_player->addGold(gold);
        m_lastMessage += " Enemy defeated! +" + std::to_string(gold) + " gold.";
        sq->removeEnemy();
    }
}

void Game::drinkPotion()
{
    const auto& inv = m_player->getInventory();
    int potIdx = -1;
    for (int i = 0; i < static_cast<int>(inv.size()); ++i)
    {
        if (inv[i]->getCategory() == ItemCategory::Potion)
        { potIdx = i; break; }
    }

    if (potIdx < 0) { m_lastMessage = "No potion in inventory."; return; }

    std::string name = inv[potIdx]->getName();
    auto potion = m_player->dropItem(potIdx);
    potion->use(*m_player);
    m_lastMessage = "Drank " + name + ".";
}

void Game::advanceTime()
{
    // time changes every 5 commands
    if (m_commandCount % 5 == 0)
    {
        m_isDay = !m_isDay;
        m_lastMessage += m_isDay ? " [Day]" : " [Night]";

        // tell the player and all enemies on the board
        m_player->updateTime(m_isDay);

        for (int y = 0; y < m_board->getHeight(); ++y)
            for (int x = 0; x < m_board->getWidth(); ++x)
            {
                Square* sq = m_board->getSquare(x, y);
                if (sq->hasEnemy())
                    sq->getEnemy()->updateTime(m_isDay);
            }
    }
}

bool Game::isRunning()  const { return m_running;  }
bool Game::isGameOver() const { return m_gameOver; }
int  Game::getPlayerX() const { return m_playerX;  }
int  Game::getPlayerY() const { return m_playerY;  }
bool Game::getIsDay()   const { return m_isDay;    }
std::string Game::getLastMessage() const { return m_lastMessage; }

const Board&     Game::getBoard()  const { return *m_board; }
const Character* Game::getPlayer() const { return m_player.get(); }
