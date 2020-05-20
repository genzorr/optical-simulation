#include "ImageCanvas.h"
#include "Transparency.h"
#include "Fourier.h"
#include <QDebug>

int WindowXSize = 1;
int WindowYSize = 1;

//const int OBJECT_CNT = 10;

ImageCanvas::ImageCanvas(QWidget *parent) : QSFMLCanvas(parent), resultObject() {}

void ImageCanvas::onInit()
{
    QSFMLCanvas::onInit();

    // Fill in resultObject properly.
    Transparency cleanObj = Transparency();
    resultObject.init(cleanObj);

    // Fill in object holder.
    objHolder.resize(1);
    objHolder.clear();

    Transparency circleObj(EDGE, 10);
    dataT lambda = 500E-9;
    CountFieldIntensity(circleObj.opaque, resultObject.opaque, 50, lambda);
    resultObject.OpaquetoImage();
//    objHolder.push_back(circleObj);
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
    WindowXSize = this->getSize().x;
    WindowYSize = this->getSize().y;
}