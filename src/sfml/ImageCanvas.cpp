#include "ImageCanvas.h"
#include "Transparency.h"
#include <QDebug>

int WindowXSize;
int WindowYSize;

//const int OBJECT_CNT = 10;

void ImageCanvas::onInit()
{
    QSFMLCanvas::onInit();

    objHolder.resize(1);
    objHolder.clear();

    Transparency circleObj(EDGE, 10);
    objHolder.push_back(circleObj);
}

void ImageCanvas::onUpdate()
{
    QSFMLCanvas::onUpdate();

    clear(sf::Color::White);

    for (auto& obj: objHolder) {
        draw(obj.sprite);
    }
}

void ImageCanvas::resizeEvent(QResizeEvent *event)
{
    QSFMLCanvas::resizeEvent(event);
    // Get image size for later usage.
    WindowXSize = this->getSize().x;
    WindowYSize = this->getSize().y;
}