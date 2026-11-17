/**
 * @file MainWindow.cpp
 * @brief Implementation of MainWindow.
 */

#include "MainWindow.h"
#include "GameWidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("Fantasy Game");
    setupUI();
}

void MainWindow::setupUI()
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    // left side: game board
    m_gameWidget = new GameWidget(this);

    // right side: stats + log + input
    m_statsLabel   = new QLabel("Press New Game to start.", this);
    m_logDisplay   = new QTextEdit(this);
    m_logDisplay->setReadOnly(true);
    m_commandInput = new QLineEdit(this);
    m_commandInput->setPlaceholderText("Type a command (n/s/e/w/p/d/a/c/k/q)...");
    m_newGameButton = new QPushButton("New Game", this);

    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->addWidget(m_statsLabel);
    rightLayout->addWidget(m_logDisplay);
    rightLayout->addWidget(m_commandInput);
    rightLayout->addWidget(m_newGameButton);

    QHBoxLayout* mainLayout = new QHBoxLayout(central);
    mainLayout->addWidget(m_gameWidget, 2);
    mainLayout->addLayout(rightLayout, 1);

    connect(m_commandInput, &QLineEdit::returnPressed,
            this, &MainWindow::onCommandEntered);
    connect(m_newGameButton, &QPushButton::clicked,
            this, &MainWindow::onNewGame);
}

void MainWindow::onNewGame()
{
    bool ok;
    QString name = QInputDialog::getText(this, "New Game",
                                         "Enter your character name:",
                                         QLineEdit::Normal, "Hero", &ok);
    if (!ok || name.isEmpty()) return;

    QStringList races = {"Human", "Elf", "Dwarf", "Hobbit", "Orc"};
    QString race = QInputDialog::getItem(this, "New Game",
                                         "Choose your race:", races, 0, false, &ok);
    if (!ok) return;

    int raceIdx = races.indexOf(race);
    m_game.newGame(10, 10, name.toStdString(), raceIdx);
    updateDisplay();
    m_commandInput->setFocus();
}

void MainWindow::onCommandEntered()
{
    QString text = m_commandInput->text().trimmed();
    m_commandInput->clear();
    if (text.isEmpty() || !m_game.isRunning()) return;

    m_game.processCommand(text[0].toLatin1());
    m_logDisplay->append(QString::fromStdString(m_game.getLastMessage()));
    updateDisplay();

    if (m_game.isGameOver())
    {
        const Character* p = m_game.getPlayer();
        QString msg = "Game Over! You collected "
                    + QString::number(p ? p->getGold() : 0)
                    + " gold.";
        QMessageBox::information(this, "Game Over", msg);
    }
}

void MainWindow::updateDisplay()
{
    // update stats label
    const Character* p = m_game.getPlayer();
    if (p)
    {
        QString stats = QString("%1 (%2)  HP: %3  Gold: %4  %5")
            .arg(QString::fromStdString(p->getName()))
            .arg(QString::fromStdString(p->getRaceName()))
            .arg(p->getHealth())
            .arg(p->getGold())
            .arg(m_game.getIsDay() ? "[Day]" : "[Night]");
        m_statsLabel->setText(stats);
    }

    // repaint the board
    m_gameWidget->setBoard(&m_game.getBoard());
    m_gameWidget->setPlayerPos(m_game.getPlayerX(), m_game.getPlayerY());
    m_gameWidget->update();
}
