/**
 * @file MainWindow.h
 * @brief The main Qt window for the game.
 */

#pragma once
#include <QMainWindow>
#include "game/Game.h"

class GameWidget;
class QLabel;
class QLineEdit;
class QTextEdit;
class QPushButton;

/**
 * @class MainWindow
 * @brief The main window. Contains the board, stats panel and command input.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    /** @brief Called when the player types a command and presses enter. */
    void onCommandEntered();

    /** @brief Called when the New Game button is clicked. */
    void onNewGame();

private:
    /** @brief Build all the widgets and lay them out. */
    void setupUI();

    /** @brief Refresh the board display and stats label. */
    void updateDisplay();

    GameWidget*  m_gameWidget;
    QLabel*      m_statsLabel;
    QLineEdit*   m_commandInput;
    QTextEdit*   m_logDisplay;
    QPushButton* m_newGameButton;

    Game m_game;
};
