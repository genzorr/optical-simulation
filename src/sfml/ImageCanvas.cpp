#include "ImageCanvas.h"
#include "Transparency.h"
#include "Fourier.h"
#include <QDebug>

int WindowXSize = 512;
int WindowYSize = 512;
int WindowXSize_2 = 256;
int WindowYSize_2 = 256;


ImageCanvas::ImageCanvas(QWidget *parent) : QSFMLCanvas(parent), resultObject() {}

void ImageCanvas::onInit()
{
    QSFMLCanvas::onInit();

    // Fill in resultObject properly.
    Transparency cleanObj = Transparency(SQUARE, 20);
    resultObject.Init(&cleanObj);
}

void ImageCanvas::onUpdate()
{
    QSFMLCanvas::onUpdate();

    clear(sf::Color::White);
    draw(resultObject.sprite);
}

void ImageCanvas::resizeEvent(QResizeEvent *event)
{
    QSFMLCanvas::resizeEvent(event);
    // Get image size for later usage.
//    WindowXSize = this->getSize().x;
//    WindowYSize = this->getSize().y;
}

Transparency *ImageCanvas::getObject()
{
    return &resultObject;
}
