#include <QApplication>
#include <QMainWindow>
#include <QtWidgets/QWidget>

#include "../interface/interface.h"
#include "sfml/QSFMLCanvas.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    Ui::MainWindow ui;

    InterfaceSetup(mainWindow, ui);
    mainWindow.showMaximized();

    return app.exec();
}