#include "ImageCanvas.h"
#include "Transparency.h"
#include "Fourier.h"
#include <QDebug>

int WindowXSize = 512;
int WindowYSize = 512;

//const int OBJECT_CNT = 10;

ImageCanvas::ImageCanvas(QWidget *parent) : QSFMLCanvas(parent), resultObject() {}

void ImageCanvas::onInit()
{
    QSFMLCanvas::onInit();
//    setSize(sf::Vector2u(256,256));

    // Fill in resultObject properly.
    Transparency cleanObj = Transparency();
    resultObject.init(cleanObj);

    // Fill in object holder.
    objHolder.resize(1);
    objHolder.clear();

    Transparency circleObj(EDGE, 20);
//    Transparency circleObj = Transparency();
    objHolder.push_back(circleObj);
//    dataT lambda = 500E-9;
//    CountFieldIntensity(circleObj.opaque, resultObject.opaque, 50, lambda);
//    resultObject.OpaquetoImage();
}

void ImageCanvas::onUpdate()
{
    QSFMLCanvas::onUpdate();

    clear(sf::Color::White);

    for (auto& obj: objHolder) {
        draw(obj.sprite);
    }
//    draw(resultObject.sprite);
}

void ImageCanvas::resizeEvent(QResizeEvent *event)
{
    QSFMLCanvas::resizeEvent(event);
    // Get image size for later usage.
//    WindowXSize = this->getSize().x;
//    WindowYSize = this->getSize().y;
}