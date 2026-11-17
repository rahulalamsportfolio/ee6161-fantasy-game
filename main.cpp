/**
 * @file main.cpp
 * @brief Entry point. Creates the Qt application and shows the main window.
 */

#include <QApplication>
#include "MainWindow.h"

/**
 * @brief Program entry point.
 * @param argc Argument count.
 * @param argv Argument values.
 * @return Exit code.
 */
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(900, 600);
    window.show();
    return app.exec();
}
