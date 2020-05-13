#include <QApplication>
#include <QMainWindow>
#include <QtWidgets/QWidget>

#include "interface.h"
#include "QSFMLCanvas.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    Ui::MainWindow ui;

    InterfaceSetup(mainWindow, ui);
    mainWindow.showMaximized();

    return app.exec();
}