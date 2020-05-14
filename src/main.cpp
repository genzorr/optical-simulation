#include <QApplication>
#include <QMainWindow>
#include <QDebug>

#include "interface.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.showFullScreen();

    return app.exec();
}