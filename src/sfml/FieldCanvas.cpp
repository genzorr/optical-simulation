#include "FieldCanvas.h"
#include "Transparency.h"
#include <iostream>


void FieldCanvas::onInit()
{
    QSFMLCanvas::onInit();

    clear(sf::Color(55, 55, 55));
}

void FieldCanvas::onUpdate()
{
    QSFMLCanvas::onUpdate();

    clear(sf::Color(55, 55, 55));

    draw(resultObject->spritePreview);
}