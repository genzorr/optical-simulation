#include <algorithm>
#include "Transparency.h"
#include "Fourier.h"
#include <QDebug>

Transparency::Transparency() : type(NO)
{
    opaque.resize(WindowXSize);
    fourierImage.resize(WindowXSize);
    for (int i = 0; i < WindowXSize; i++)
    {
        opaque[i].resize(WindowYSize);
        std::fill(opaque[i].begin(), opaque[i].end(), 1);

        fourierImage[i].resize(WindowYSize);
        std::fill(fourierImage[i].begin(), fourierImage[i].end(), complex(1, 0));
    }

    CreateFourierImage();

    image.create(WindowXSize, WindowYSize, sf::Color::White);
    texture.create(WindowXSize, WindowYSize);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

Transparency::Transparency(ObjType objType, int XSize) : type(objType)
{
    opaque.resize(WindowXSize);
    fourierImage.resize(WindowXSize);
    for (int i = 0; i < WindowXSize; i++)
    {
        opaque[i].resize(WindowYSize);
        std::fill(opaque[i].begin(), opaque[i].end(), 0);

        fourierImage[i].resize(WindowYSize);
        std::fill(fourierImage[i].begin(), fourierImage[i].end(), complex(0, 0));
    }

    image.create(WindowXSize, WindowYSize, sf::Color::Black);

    if (objType == EDGE)
    {
        int edgeXCoordinate = (WindowXSize / 2) - XSize;
        for (int x = edgeXCoordinate; x < WindowXSize; x++)
        {
            std::fill(opaque[x].begin(), opaque[x].end(), 1.0);
            for (int y = 0; y < WindowYSize; y++)
                image.setPixel(x, y, sf::Color(255, 0, 0));
        }
    }
    else if (objType == SQUARE)
    {
        int left = (int)((WindowXSize - XSize) / 2);
        int top = (int)((WindowYSize - XSize) / 2);

        for (int x = left; x < (WindowXSize - left); x++)
        {
            for (int y = top; y < (WindowYSize - top); y++)
            {
                opaque[x][y] = 1;
                image.setPixel(x, y, sf::Color(255, 0, 0));
            }
        }
    }

    CreateFourierImage();

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

    fourierImage.resize(0);
    for (int i = 0; i < object.fourierImage.size(); i++)
        fourierImage.push_back(object.fourierImage[i]);

    const sf::Rect rect(0,0, WindowXSize, WindowYSize);
    image.create(WindowXSize, WindowYSize, sf::Color::Black);
    image.copy(object.image, 0, 0, rect, true);

    texture.create(WindowXSize, WindowYSize);
    texture.update(image);

    sprite.setTexture(texture, true); // don't forget to reset sprite's rect!!
}

void Transparency::CopyOpaqueFourier()
{
    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
            fourierImage[x][y] = complex(opaque[x][y], 0);
    }
}

void Transparency::OpaqueImage()
{
    if ((image.getSize().x != WindowXSize) or (image.getSize().y != WindowYSize))
        image.create(WindowXSize, WindowYSize, sf::Color::Black);

    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            image.setPixel(x, y, sf::Color(opaque[x][y], 0, 0, 255)); //(sf::Uint8)((1-opaque[x][y])*255)
        }
    }

    texture.create(WindowXSize, WindowYSize);
    texture.update(image);
    sprite.setTexture(texture, true);
}

void Transparency::CreateFourierImage()
{
    CopyOpaqueFourier();
    FFT2D(fourierImage, WindowXSize, WindowYSize, 1);
}

void Transparency::CreateInverseFourierImage()
{
    FFT2D(fourierImage, WindowXSize, WindowYSize, -1);
}

void Transparency::ApplyFourierImage()
{
    if ((image.getSize().x != WindowXSize) or (image.getSize().y != WindowYSize))
        image.create(WindowXSize, WindowYSize, sf::Color::Black);

    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            int pixel = std::min(int(std::abs(fourierImage[x][y])*255), 255);
            image.setPixel(x, y, sf::Color(pixel, 0, 0)); //(sf::Uint8)((1-std::abs(fourierImage[x][y]))*255))
        }
    }

    texture.create(WindowXSize, WindowYSize);
    texture.update(image);
    sprite.setTexture(texture, true);
}

void Transparency::CreateImage(dataT z, dataT lambda)
{
    CreateFourierImage();

    dataT k_z = z * 2 * M_PI / lambda;
    dataT z_2 = z*z;

    for (int x = 0; x < WindowXSize; x++)
    {
        dataT x_2 = x*x;
        for (int y = 0; y < WindowYSize; y++)
        {
            dataT value = k_z / sqrt(x_2 + y*y + z_2);
            complex exp(cos(value), -sin(value));
            fourierImage[x][y] *= exp;
        }
    }

    CreateInverseFourierImage();
    ApplyFourierImage();
}