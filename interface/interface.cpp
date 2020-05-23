#include <QMainWindow>
#include <QDebug>
#include <QFrame>
#include <QMoveEvent>

#include "interface.h"
#include "FieldCanvas.h"
#include "ImageCanvas.h"


MainWindow::MainWindow()
{
//    uncomment if you want your app be not fullscreen
//    time: 3 hours of stupid work, and this thing doesnt work properly
//    resizeTimer.setSingleShot( true );
//    connect( &resizeTimer, SIGNAL(timeout()), SLOT(resizeDone()));

    Ui::MainWindow ui;
    ui.setupUi(this);

    ///Resulting image
    ImageCanvas* imageCanvas = new ImageCanvas(ui.imageFrame);
    ui.hl12->addWidget(imageCanvas);

    //FIXME: 1st line for 1920x1080, 2nd for ultrawide
    //ui.hl12->setContentsMargins(125, 98, 124, 98);
    ui.hl12->setContentsMargins(251, 96, 251, 96);

    ///Preview of scene
    FieldCanvas* fieldCanvas = new FieldCanvas(ui.fieldFrame);
    fieldCanvas->setObject(imageCanvas->getObject());
    ui.hl11->addWidget(fieldCanvas);

    connect(ui.sizeBox, QOverload<int>::of(&QSpinBox::valueChanged), &(imageCanvas->resultObject), &Transparency::UpdateSize);
    connect(ui.fourierButton, &QPushButton::pressed, &(imageCanvas->resultObject), &Transparency::UpdateFourier);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    if (!m_resizeDone)
    {
        resizeTimer.start(500);
        QMainWindow::resizeEvent(event);
        m_resizeDone = true;
    }
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    event->ignore();
}

void MainWindow::resizeDone()
{
    setFixedSize(size());
    setMinimumSize(size());
}