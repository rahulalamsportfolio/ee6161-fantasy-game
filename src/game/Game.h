/**
 * @file Game.h
 * @brief Main game logic. Runs the game loop and handles all commands.
 */

#pragma once
#include <string>
#include <memory>
#include "Board.h"

class Character;

/**
 * @class Game
 * @brief Manages game state and processes player commands.
 */
class Game
{
public:
    Game();

    /**
     * @brief Start a new game.
     * @param width       Board width.
     * @param height      Board height.
     * @param playerName  The player's name.
     * @param raceChoice  0=Human 1=Elf 2=Dwarf 3=Hobbit 4=Orc.
     */
    void newGame(int width, int height, const std::string& playerName, int raceChoice);

    /**
     * @brief Process one command from the player.
     * @param cmd The command character (n/s/e/w/p/d/a/c/k/q).
     */
    void processCommand(char cmd);

    bool isRunning()  const;
    bool isGameOver() const;

    const Board&     getBoard()   const;
    const Character* getPlayer()  const;
    int  getPlayerX() const;
    int  getPlayerY() const;
    bool getIsDay()   const;

    /** @return The last message produced by the game (for the log). */
    std::string getLastMessage() const;

private:
    void movePlayer(int dx, int dy);
    void attackEnemy();
    void pickUpItem();
    void dropItem();
    void castSpell();
    void drinkPotion();
    void advanceTime();

    /**
     * @brief Resolve one attack from attacker to defender.
     * @return Text describing what happened.
     */
    std::string resolveAttack(Character& attacker, Character& defender);

    std::unique_ptr<Board>     m_board;
    std::unique_ptr<Character> m_player;
    int  m_playerX, m_playerY;
    int  m_commandCount;
    bool m_isDay;
    bool m_running;
    bool m_gameOver;
    std::string m_lastMessage;
};
