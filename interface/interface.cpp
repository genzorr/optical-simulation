#include <QMainWindow>
#include <QSizePolicy>
#include <QFrame>

#include "interface.h"
#include "FieldCanvas.h"
#include "ImageCanvas.h"

void InterfaceSetup(QMainWindow& window, Ui::MainWindow& ui)
{
    ui.setupUi(&window);

    FieldCanvas* fieldCanvas = new FieldCanvas(ui.fieldFrame);
    fieldCanvas->show();

    ImageCanvas* imageCanvas = new ImageCanvas(ui.imageFrame);
    imageCanvas->show();
}
