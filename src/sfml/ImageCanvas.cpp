#include "ImageCanvas.h"

int WindowXSize;
int WindowYSize;

void ImageCanvas::onInit()
{
    QSFMLCanvas::onInit();

    clear(sf::Color::Red);
}

void ImageCanvas::onUpdate()
{
    QSFMLCanvas::onUpdate();

    clear(sf::Color::Red);
}

void ImageCanvas::resizeEvent(QResizeEvent *event)
{
    QSFMLCanvas::resizeEvent(event);
    // Get image size for later usage.
    WindowXSize = this->getSize().x;
    WindowYSize = this->getSize().y;
}