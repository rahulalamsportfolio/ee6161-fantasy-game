/**
 * @file Board.h
 * @brief The game board, a grid of squares.
 *
 * Each square is managed with a unique_ptr so memory is handled automatically.
 */

#pragma once
#include <vector>
#include <memory>
#include "Square.h"

/**
 * @class Board
 * @brief A rectangular grid of Square objects.
 */
class Board
{
public:
    /**
     * @brief Create a board of the given size.
     * @param width  Number of columns.
     * @param height Number of rows.
     */
    Board(int width, int height);

    int getWidth()  const;
    int getHeight() const;

    /**
     * @brief Get the square at a position.
     * @param x Column (0 = left).
     * @param y Row (0 = top).
     * @return Pointer to the square, or nullptr if out of bounds.
     */
    Square* getSquare(int x, int y) const;

    /** @brief Check if a position is inside the board. */
    bool isValid(int x, int y) const;

    /**
     * @brief Fill the board with random enemies and items.
     *        Called once at the start of a new game.
     */
    void initialise();

private:
    int m_width, m_height;

    // 2D grid - each square is owned by a unique_ptr
    std::vector<std::vector<std::unique_ptr<Square>>> m_grid;
};
