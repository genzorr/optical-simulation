#include <QMainWindow>
#include <QSizePolicy>
#include <QFrame>
#include "interface.h"
#include "../src/sfml/QSFMLCanvas.h"

void InterfaceSetup(QMainWindow& window, Ui::MainWindow& ui)
{
    ui.setupUi(&window);

    QSFMLCanvas* fieldCanvas = new QSFMLCanvas(ui.fieldFrame, 50);
    fieldCanvas->show();

    QSFMLCanvas* imageCanvas = new QSFMLCanvas(ui.imageFrame, 50);
    imageCanvas->show();
}
