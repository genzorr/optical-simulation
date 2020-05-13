#include "parameters.h"
#include "ImageCanvas.h"

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
    QSFMLCanvas::onInit();

    clear(sf::Color::Red);
}