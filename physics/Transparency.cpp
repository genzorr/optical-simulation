#include <algorithm>
#include "Transparency.h"
#include <QDebug>

Transparency::Transparency() : type(NO)
{
    opaque.resize(WindowXSize);
    for (auto& item: opaque) {
        item.resize(WindowYSize);
        std::fill(item.begin(), item.end(), 0);
    }
    image.create(WindowXSize, WindowYSize, sf::Color::White);
    texture.create(WindowXSize, WindowYSize);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

Transparency::Transparency(ObjType objType, int XSize) : type(objType)
{
    opaque.resize(WindowXSize);
    for (auto& item: opaque) {
        item.resize(WindowYSize);
        std::fill(item.begin(), item.end(), 0);
    }

    image.create(WindowXSize, WindowYSize, sf::Color::Black);

    if (objType == EDGE)
    {
        int edgeXCoordinate = (WindowXSize / 2) - XSize;
        for (int x = edgeXCoordinate; x < WindowXSize; x++)
        {
//            if (x < edgeXCoordinate)
//            {
//                std::fill(opaque[x].begin(), opaque[x].end(), 0.0);
//                for (int y = 0; y < WindowYSize; y++)
//                    image.setPixel(x, y, sf::Color::Black);
//            }
//            else
//            {
                std::fill(opaque[x].begin(), opaque[x].end(), 1.0);
                for (int y = 0; y < WindowYSize; y++)
                    image.setPixel(x, y, sf::Color::White);
//            }
        }
    }

    texture.create(WindowXSize, WindowYSize);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

Transparency::Transparency(dataT2D &field, int XSize, int YSize)
{

}

Transparency::Transparency(const Transparency &object)
{
    init(object);
}

void Transparency::init(const Transparency &object)
{
    type = object.type;

    opaque.resize(0);
    for (int i = 0; i < object.opaque.size(); i++)
        opaque.push_back(object.opaque[i]);

    const sf::Rect rect(0,0, WindowXSize, WindowYSize);
    image.create(WindowXSize, WindowYSize, sf::Color::Black);
    image.copy(object.image, 0, 0, rect, true);

    texture.create(WindowXSize, WindowYSize);
    texture.update(image);

    sprite.setTexture(texture, true); // don't forget to reset sprite's rect!!
}

void Transparency::OpaquetoImage()
{
    if ((image.getSize().x != WindowXSize) or (image.getSize().y != WindowYSize))
        image.create(WindowXSize, WindowYSize, sf::Color::Black);

    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            image.setPixel(x, y, sf::Color(0, 0, 0, (sf::Uint8)((1-opaque[x][y])*255)));
        }
    }

    texture.create(WindowXSize, WindowYSize);
    texture.update(image);

    sprite.setTexture(texture, true);
}