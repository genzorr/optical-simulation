#include "parameters.h"
#include "ImageCanvas.h"
#include <QDebug>

int WindowXSize;
int WindowYSize;

void ImageCanvas::onInit()
{
    QSFMLCanvas::onInit();

    // Get image size for later usage.
    WindowXSize = this->getSize().x;
    WindowYSize = this->getSize().y;

    clear(sf::Color::Red);
}

void ImageCanvas::onUpdate()
{
    QSFMLCanvas::onUpdate();

    // Get image size for later usage.
    WindowXSize = this->getSize().x;
    WindowYSize = this->getSize().y;

    qDebug() << WindowXSize << WindowYSize;

    clear(sf::Color::Red);
}