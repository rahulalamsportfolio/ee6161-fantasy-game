/**
 * @file GameWidget.cpp
 * @brief Implementation of GameWidget.
 */

#include "GameWidget.h"
#include "game/Board.h"
#include "game/Square.h"
#include <QPainter>
#include <QColor>

GameWidget::GameWidget(QWidget* parent) : QWidget(parent)
{
    setMinimumSize(400, 400);
}

void GameWidget::setBoard(const Board* board)  { m_board   = board; }
void GameWidget::setPlayerPos(int x, int y)    { m_playerX = x; m_playerY = y; }

void GameWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    if (!m_board) return;

    for (int y = 0; y < m_board->getHeight(); ++y)
    {
        for (int x = 0; x < m_board->getWidth(); ++x)
        {
            QRect cell(x * CELL, y * CELL, CELL - 1, CELL - 1);
            Square* sq = m_board->getSquare(x, y);

            if (x == m_playerX && y == m_playerY)
            {
                painter.fillRect(cell, QColor(50, 150, 255));  // blue = player
                painter.setPen(Qt::white);
                painter.drawText(cell, Qt::AlignCenter, "P");
            }
            else if (sq && sq->hasEnemy())
            {
                painter.fillRect(cell, QColor(200, 50, 50));   // red = enemy
                painter.setPen(Qt::white);
                painter.drawText(cell, Qt::AlignCenter, "E");
            }
            else if (sq && sq->hasItem())
            {
                painter.fillRect(cell, QColor(50, 180, 50));   // green = item
                painter.setPen(Qt::white);
                painter.drawText(cell, Qt::AlignCenter, "I");
            }
            else
            {
                painter.fillRect(cell, QColor(60, 60, 60));    // grey = empty
            }

            painter.setPen(QColor(80, 80, 80));
            painter.drawRect(cell);
        }
    }
}
