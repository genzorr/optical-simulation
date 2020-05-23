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
    Transparency cleanObj = Transparency(SQUARE, 2);
    resultObject.Init(cleanObj);

    // Fill in object holder.
    objHolder.resize(1);
    objHolder.clear();

    dataT lambda = 500E-9;

    Transparency edge(EDGE, 30);
    edge.CreateImage(0.3, lambda, 10E-6);
//    objHolder.push_back(edge);

    Transparency gap(GAP, 50);
    gap.CreateImage(1, lambda, 10E-6);
//    objHolder.push_back(gap);


    Transparency square(SQUARE, 64);
//    square.CreateImage(1, lambda, 10E-6);
//    square.CreateFourierImage();
//    square.ApplyFourierImage();
//    objHolder.push_back(square);
}

void ImageCanvas::onUpdate()
{
    QSFMLCanvas::onUpdate();

    clear(sf::Color::White);

//    for (auto& obj: objHolder) {
//        draw(obj.sprite);
//    }
    draw(resultObject.sprite);
}

void ImageCanvas::resizeEvent(QResizeEvent *event)
{
    QSFMLCanvas::resizeEvent(event);
    // Get image size for later usage.
//    WindowXSize = this->getSize().x;
//    WindowYSize = this->getSize().y;
}

Transparency *ImageCanvas::getObject() {
    return &resultObject;
}
