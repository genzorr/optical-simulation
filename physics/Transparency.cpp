#include <algorithm>
#include "Transparency.h"
#include <QDebug>

Transparency::Transparency() :
    type(NO)
{
    opaque.resize(WindowXSize);
    for (auto& item: opaque) {
        item.resize(WindowYSize);
        std::fill(item.begin(), item.end(), 0);
    }
}

Transparency::Transparency(const Transparency &object)
{
    type = object.type;

    opaque = object.opaque;

    image.copy(object.image, WindowXSize, WindowYSize, sf::IntRect(0,0,WindowXSize, WindowYSize));
    image = object.image;
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

Transparency::Transparency(ObjType objType, int XSize) :
        type(objType)
{
    opaque.resize(WindowXSize);
    for (auto& item: opaque) {
        item.resize(WindowYSize);
        std::fill(item.begin(), item.end(), 0);
    }

    image.create(WindowXSize, WindowYSize, sf::Color::Black);
    texture.create(WindowXSize, WindowYSize);

    if (objType == EDGE)
    {
        int edgeXCoordinate = (WindowXSize / 2) - XSize;
        for (int x = 0; x < WindowXSize; x++)
        {
            if (x < edgeXCoordinate)
            {
                std::fill(opaque[x].begin(), opaque[x].end(), 0.0);
                for (int y = 0; y < WindowYSize; y++)
                    image.setPixel(x, y, sf::Color::Black);
            }
            else
            {
                std::fill(opaque[x].begin(), opaque[x].end(), 1.0);
                for (int y = 0; y < WindowYSize; y++)
                    image.setPixel(x, y, sf::Color::White);
            }
        }
    }

    texture.create(WindowXSize, WindowYSize);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

Transparency::Transparency(dataT2D &field, int XSize, int YSize)
{

}