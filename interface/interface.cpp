#include <QMainWindow>
#include <QDebug>
#include <QFrame>
#include <QMoveEvent>

#include "interface.h"
#include "FieldCanvas.h"
#include "ImageCanvas.h"
#include "FourierCanvas.h"


MainWindow::MainWindow()
{
///    uncomment if you want your app be not fullscreen
///    time: 3 hours of stupid work, and this thing doesnt work properly
//    resizeTimer.setSingleShot( true );
//    connect( &resizeTimer, SIGNAL(timeout()), SLOT(resizeDone()));

    Ui::MainWindow ui;
    ui.setupUi(this);

    /// Preview of scene
    FieldCanvas* fieldCanvas = new FieldCanvas(ui.fieldFrame);
    ui.hl11->addWidget(fieldCanvas);

    /// Resulting image
    ImageCanvas* imageCanvas = new ImageCanvas(ui.imageFrame);
    ui.hl12->addWidget(imageCanvas);

    /// Fourier image
    FourierCanvas* fourierCanvas = new FourierCanvas(ui.fourierFrame);
    ui.hl13->addWidget(fourierCanvas);


    /// Get object
    fieldCanvas->setObject(imageCanvas->getObject());
    fourierCanvas->setObject(imageCanvas->getObject());


    //FIXME: 1st 3 lines for 1920x1080, 2nd  3 lines for 2560x1080
    ui.hl11->setContentsMargins(60, 98, 60, 98);
    ui.hl12->setContentsMargins(60, 98, 60, 98);
    ui.hl13->setContentsMargins(60, 98, 60, 98);
//    ui.hl11->setContentsMargins(165, 96, 165, 96);
//    ui.hl12->setContentsMargins(165, 96, 165, 96);
//    ui.hl13->setContentsMargins(165, 96, 165, 96);

    INIT_SIZE = ui.sizeValue->value();
    DIST = ui.distValue->value();
    ui.sizeDisplay->display(INIT_SIZE);
    imageCanvas->UpdateLambda(DEFAULT_WAVELEN);

    /// Update size of result object.
    connect(ui.sizeValue, SIGNAL(valueChanged(int)), ui.sizeDisplay, SLOT(display(int)));
    connect(ui.sizeValue, SIGNAL(valueChanged(int)), &(imageCanvas->resultObject), SLOT(Update(int)));

    /// Update lambda value from slider.
    ui.lambdaDisplay->display(ui.lambdaValue->value());
    connect(ui.lambdaValue, SIGNAL(valueChanged(int)), ui.lambdaDisplay, SLOT(display(int)));
    connect(ui.lambdaValue, SIGNAL(valueChanged(int)), imageCanvas, SLOT(UpdateLambda(int)));

    /// Update distance.
    ui.distDisplay->display(ui.distValue->value());
    connect(ui.distValue, SIGNAL(valueChanged(int)), ui.distDisplay, SLOT(display(int)));
    connect(ui.distValue, SIGNAL(valueChanged(int)), imageCanvas, SLOT(UpdateDistance(int)));
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