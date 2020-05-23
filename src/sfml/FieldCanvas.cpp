#include "FieldCanvas.h"
#include "Transparency.h"
#include <iostream>


void FieldCanvas::onInit()
{
    QSFMLCanvas::onInit();

    clear(sf::Color::Blue);


}

void FieldCanvas::onUpdate()
{
    QSFMLCanvas::onUpdate();

    clear(sf::Color::Blue);

    draw(resultObject->spritePreview);

    //draw(resultObject->sprite);
}