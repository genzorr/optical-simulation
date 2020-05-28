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
    /// Update size for result object
    connect(ui.sizeBox, QOverload<int>::of(&QSpinBox::valueChanged), &(imageCanvas->resultObject), &Transparency::Update);
    /// For fourier image< update size and set it's output image
//    connect(ui.sizeBox, QOverload<int>::of(&QSpinBox::valueChanged), &(fourierCanvas->resultObject), &Transparency::UpdateSize);
//    connect(ui.sizeBox, QOverload<int>::of(&QSpinBox::valueChanged), &(fourierCanvas->resultObject), &Transparency::UpdateFourier);
    /// Manually update output fourier image
    //connect(ui.fourierButton, &QPushButton::pressed, &(fourierCanvas->resultObject), &Transparency::UpdateFourier);
//    fourierCanvas->resultObject.UpdateFourier();

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