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
    image.create(WindowXSize, WindowYSize, sf::Color::Black);

    Update(XSize);
}

Transparency::Transparency(dataT2D &field, int XSize, int YSize)
{

}

Transparency::Transparency(const Transparency &object)
{
    Init(object);
}

void Transparency::Init(const Transparency &object)
{
    type = object.type;

    opaque.resize(0);
    for (size_t i = 0; i < object.opaque.size(); i++)
        opaque.push_back(object.opaque[i]);

    fourierImage.resize(0);
    for (size_t i = 0; i < object.fourierImage.size(); i++)
        fourierImage.push_back(object.fourierImage[i]);

    const sf::Rect rect(0,0, WindowXSize, WindowYSize);
    image.create(WindowXSize, WindowYSize, sf::Color::Black);
    image.copy(object.image, 0, 0, rect, true);

    texture.create(WindowXSize, WindowYSize);
    texture.update(image);

    sprite.setTexture(texture, true); // don't forget to reset sprite's rect!!
}

void Transparency::Update(int XSize)
{
    for (int i = 0; i < WindowXSize; i++)
    {
        opaque[i].resize(WindowYSize);
        std::fill(opaque[i].begin(), opaque[i].end(), 0);

        fourierImage[i].resize(WindowYSize);
        std::fill(fourierImage[i].begin(), fourierImage[i].end(), complex(0, 0));
    }

    if (type == EDGE)
    {
        int edgeXCoordinate = (WindowXSize / 2) - XSize;
        for (int x = edgeXCoordinate; x < WindowXSize; x++)
        {
            std::fill(opaque[x].begin(), opaque[x].end(), 1.0);
            for (int y = 0; y < WindowYSize; y++)
                image.setPixel(x, y, sf::Color(255, 0, 0));
        }
    }
    else if (type == GAP)
    {
        int left = (int)((WindowXSize - XSize) / 2);
        for (int x = left; x < WindowXSize - left; x++)
        {
            std::fill(opaque[x].begin(), opaque[x].end(), 1.0);
            for (int y = 0; y < WindowYSize; y++)
                image.setPixel(x, y, sf::Color(255, 0, 0));
        }
    }
    else if (type == SQUARE)
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
            image.setPixel(x, y, sf::Color((int)(opaque[x][y]*255), 0, 0));
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
            complex value = fourierImage[x][y];
            dataT intense = value.real() * value.real() + value.imag() * value.imag();
//            dataT intense = value.real();
            int pixel = std::min(int(intense*255), 255);
            image.setPixel(x, y, sf::Color((sf::Uint8)pixel, 0, 0)); //(sf::Uint8)((1-std::abs(fourierImage[x][y]))*255))
        }
    }

    texture.create(WindowXSize, WindowYSize);
    texture.update(image);
    sprite.setTexture(texture, true);
}

void Transparency::CreateImage(dataT z, dataT lambda, dataT scale)
{
    CreateFourierImage();

    dataT z_2 = z*z; // m^2
    dataT k_z_2 = z_2 * 2 * M_PI / lambda; // m
    dataT scale_2 = scale*scale;

    for (int x = 0; x < WindowXSize; x++)
    {
        dataT x_2 = x * x * scale_2;
        for (int y = 0; y < WindowYSize; y++)
        {
            dataT value = k_z_2 / sqrt(x_2 + y*y*scale_2 + z_2);
            complex exp(cos(value), -sin(value));
            fourierImage[x][y] *= exp;
        }
    }

    CreateInverseFourierImage();
    ApplyFourierImage();
}

void Transparency::FourierNormalize()
{
    dataT max = 0;
    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            dataT value = std::abs(fourierImage[x][y]);
            if (value > max)
                max = value;
        }
    }

    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            fourierImage[x][y] /= max;
        }
    }
}

void Transparency::UpdateSize(int size)
{
    Update(size);
//    OpaqueImage();
    CreateImage(1, 500E-9, 10E-6);
}

void Transparency::UpdateFourier()
{
    CreateFourierImage();
    ApplyFourierImage();
}