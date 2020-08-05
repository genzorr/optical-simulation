#include "FourierCanvas.h"
#include <iostream>

void FourierCanvas::onInit()
{
    QSFMLCanvas::onInit();

    clear(sf::Color(55, 55, 55));
}

void FourierCanvas::onUpdate()
{
    QSFMLCanvas::onUpdate();

    clear(sf::Color(55, 55, 55));

    draw(resultObject->spriteFourier);
}