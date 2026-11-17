/**
 * @file GameWidget.h
 * @brief Widget that draws the game board as a grid of coloured tiles.
 */

#pragma once
#include <QWidget>

class Board;

/**
 * @class GameWidget
 * @brief Draws the board. Each cell shows the player, an enemy, an item or empty space.
 */
class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget* parent = nullptr);

    /** @brief Give the widget a board to draw. */
    void setBoard(const Board* board);

    /** @brief Set where the player is so it can be highlighted. */
    void setPlayerPos(int x, int y);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    const Board* m_board   = nullptr;
    int          m_playerX = 0;
    int          m_playerY = 0;

    static constexpr int CELL = 40; // pixel size of each cell
};
