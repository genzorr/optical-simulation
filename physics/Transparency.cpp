#include <algorithm>
#include "Transparency.h"
#include "Fourier.h"
#include <QDebug>
#include "../util/waveRGB/waveRGB.h"


Transparency::Transparency() : type(NO)
{
    relativeOpaque.resize(WindowXSize);
    absoluteOpaque.resize(WindowXSize);
    fourierImage.resize(WindowXSize);
    for (int i = 0; i < WindowXSize; i++)
    {
        relativeOpaque[i].resize(WindowYSize);
        std::fill(relativeOpaque[i].begin(), relativeOpaque[i].end(), 1);

        fourierImage[i].resize(WindowYSize);
        std::fill(fourierImage[i].begin(), fourierImage[i].end(), complex(1, 0));
    }

    CountFourierImage();

    image.create(WindowXSize, WindowYSize, sf::Color::White);
    texture.create(WindowXSize, WindowYSize);
    texture.loadFromImage(image);
    sprite.setTexture(texture);

    ///Init everything for preview
    imagePreview.create(WindowXSize, WindowYSize, sf::Color::White);
    texturePreview.create(WindowXSize, WindowYSize);
    texturePreview.loadFromImage(imagePreview);
    spritePreview.setTexture(texturePreview);

    createPreview({100, 100}, PREVIEW_PIXEL_SIZE);

}

Transparency::Transparency(ObjType objType, int XSize) : type(objType)
{
    relativeOpaque.resize(WindowXSize);
    absoluteOpaque.resize(WindowXSize);
    fourierImage.resize(WindowXSize);
    image.create(WindowXSize, WindowYSize, sf::Color::Black);
    imagePreview.create(WindowXSize, WindowYSize, sf::Color::Black);

    Update(XSize);
}

Transparency::Transparency(dataT2D &field, int XSize, int YSize)
{

}

Transparency::Transparency(const Transparency &object)
{
    Init(object);
    createPreview({0, 0}, PREVIEW_PIXEL_SIZE);
}

void Transparency::Init(const Transparency &object)
{
    type = object.type;

    relativeOpaque.resize(0);
    absoluteOpaque.resize(0);
    for (size_t i = 0; i < object.relativeOpaque.size(); i++)
        relativeOpaque.push_back(object.relativeOpaque[i]);
    for (size_t i = 0; i < object.absoluteOpaque.size(); i++)
        absoluteOpaque.push_back(object.absoluteOpaque[i]);

    fourierImage.resize(0);
    for (size_t i = 0; i < object.fourierImage.size(); i++)
        fourierImage.push_back(object.fourierImage[i]);

    const sf::Rect rect(0,0, WindowXSize, WindowYSize);
    image.create(WindowXSize, WindowYSize, sf::Color::Black);
    image.copy(object.image, 0, 0, rect, true);

    texture.create(WindowXSize, WindowYSize);
    texture.update(image);

    sprite.setTexture(texture, true); // don't forget to reset sprite's rect!!


    ///Set everything for preview
    imagePreview.create(WindowXSize, WindowYSize, sf::Color::Black);
    imagePreview.copy(object.imagePreview, 0, 0, rect, true);
    texturePreview.create(WindowXSize, WindowYSize);
    texturePreview.update(imagePreview);
    spritePreview.setTexture(texturePreview, true);

    createPreview({0, 0}, PREVIEW_PIXEL_SIZE);
}

void Transparency::Update(int XSize)
{
    for (int i = 0; i < WindowXSize; i++)
    {
        absoluteOpaque[i].resize(WindowYSize);
        relativeOpaque[i].resize(WindowYSize);
        std::fill(absoluteOpaque[i].begin(), absoluteOpaque[i].end(), 0);
        std::fill(relativeOpaque[i].begin(), relativeOpaque[i].end(), 0);

        fourierImage[i].resize(WindowYSize);
        std::fill(fourierImage[i].begin(), fourierImage[i].end(), complex(0, 0));
    }

    if (type == EDGE)
    {
        int edgeXCoordinate = (WindowXSize / 2) - XSize;
        for (int x = edgeXCoordinate; x < WindowXSize; x++)
        {
            std::fill(absoluteOpaque[x].begin(), absoluteOpaque[x].end(), 1.0);
            for (int y = 0; y < WindowYSize; y++)
                image.setPixel(x, y, sf::Color(255, 0, 0));
        }
    }
    else if (type == GAP)
    {
        int left = (int)((WindowXSize - XSize) / 2);
        for (int x = left; x < WindowXSize - left; x++)
        {
            std::fill(absoluteOpaque[x].begin(), absoluteOpaque[x].end(), 1.0);
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
                absoluteOpaque[x][y] = 1;
                image.setPixel(x, y, sf::Color(255, 0, 0));
            }
        }
    }

    setRelativeOpaque();

    CountFourierImage();

    texture.create(WindowXSize, WindowYSize);
    texture.loadFromImage(image);
    sprite.setTexture(texture);

    texturePreview.create(WindowXSize, WindowYSize);

    createPreview({0, 0}, PREVIEW_PIXEL_SIZE);

    texturePreview.loadFromImage(imagePreview);
    spritePreview.setTexture(texturePreview, true);


}

void Transparency::CopyOpaqueFourier()
{
    setRelativeOpaque();
    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
            fourierImage[x][y] = complex(255 * relativeOpaque[x][y], 0);
    }
}

void Transparency::relativeOpaqueImage() {
    if ((image.getSize().x != WindowXSize) or (image.getSize().y != WindowYSize))
        image.create(WindowXSize, WindowYSize, sf::Color::Black);

    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            image.setPixel(x, y, sf::Color((int)(relativeOpaque[x][y] * 255), 0, 0));
        }
    }

    texture.create(WindowXSize, WindowYSize);
    texture.update(image);
    sprite.setTexture(texture, true);
}

void Transparency::createPreview(sf::Vector2i position, int pixelSize)
{
    if ((imagePreview.getSize().x != WindowXSize) or (imagePreview.getSize().y != WindowYSize))
        imagePreview.create(WindowXSize, WindowYSize, sf::Color::Black);

    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            imagePreview.setPixel(x, y, sf::Color(relativeOpaque[x][y] * 255, relativeOpaque[x][y] * 255, relativeOpaque[x][y] * 255));
        }
    }

    texturePreview.create(WindowXSize, WindowYSize);
    texturePreview.update(imagePreview, WindowXSize, WindowYSize);
    spritePreview.setTexture(texturePreview, true);
//    spritePreview.setPosition(position.x, position.y);
    spritePreview.setScale(pixelSize/512.f, pixelSize/512.f);
}

void Transparency::CountFourierImage()
{
    CopyOpaqueFourier();
    FFT2D(fourierImage, WindowXSize, WindowYSize, 1);
    FourierTranslateNormalize();
}

void Transparency::CountInverseFourierImage()
{
    FFT2D(fourierImage, WindowXSize, WindowYSize, -1);
    FourierNormalize();
//    FourierTranslateNormalize();
}

void Transparency::FourierTranslateNormalize()
{
    dataT max = 0;
    dataT2Dc copy(WindowXSize);
    for (int x = 0; x < WindowXSize; x++)
    {
        copy[x].resize(WindowYSize);
        for (int y = 0; y < WindowYSize; y++)
        {
            copy[x][y] = fourierImage[x][y];
            dataT value = std::abs(fourierImage[x][y]);
            if (value > max)
                max = value;
        }
    }

    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            int newx = (x < WindowXSize_2) ? (WindowXSize_2 - x - 1) : (WindowXSize + WindowXSize_2 - x - 1);
            int newy = (y < WindowYSize_2) ? (WindowYSize_2 - y - 1) : (WindowYSize + WindowYSize_2 - y - 1);
            fourierImage[x][y] = 255.0 * copy[newx][newy] / max;
        }
    }

}

void Transparency::CreateFourierImage()
{
    if ((image.getSize().x != WindowXSize) or (image.getSize().y != WindowYSize))
        image.create(WindowXSize, WindowYSize, sf::Color::Black);

    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            complex value = fourierImage[x][y];
            dataT intense = std::abs(value);
            int pixel = std::min(int(intense), 255);
            // TODO: refactor this, maybe move calculating rgbColor to Init or smth.
            sf::Color pixelColor = WaveRGB::Calc(500);
            pixelColor.r *= pixel / 255.f;
            pixelColor.g *= pixel / 255.f;
            pixelColor.b *= pixel / 255.f;
            //
            image.setPixel(x, y, pixelColor);
        }
    }

    texture.create(WindowXSize, WindowYSize);
    texture.update(image);
    sprite.setTexture(texture, true);
}

void Transparency::CreateImage(dataT z, dataT lambda, dataT scale)
{
    CountFourierImage();

    dataT z_2 = z*z; // m^2
    dataT k_z_2 = z_2 * 2 * M_PI / lambda; // m
    dataT scale_2 = scale*scale;

    /// Iterate through all x y and apply z offset like in lectures
    for (int x = -WindowXSize/2; x < WindowXSize/2; x++)
    {
        dataT x_2 = x * x * scale_2;
        for (int y = -WindowXSize/2; y < WindowYSize/2; y++)
        {
            dataT value = -k_z_2 * sqrt(x_2 + y*y*scale_2 + z_2);
            complex exp(cos(value), sin(value));
            fourierImage[x + WindowXSize/2][y + WindowXSize/2] *= exp;
        }
    }

    CountInverseFourierImage();
    CreateFourierImage();
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
            fourierImage[x][y] = 255.0 * fourierImage[x][y] / max;
        }
    }
}

void Transparency::UpdateSize(int size)
{
    Update(size);
//    relativeOpaqueImage();
    CreateImage(10, 500E-9, 10E-6);
}

void Transparency::UpdateFourier()
{
    CountFourierImage();
    CreateFourierImage();
}

void Transparency::setRelativeOpaque(const Transparency *object) {
    /// If it is 1st object
    if (object == nullptr) {
        for (size_t i = 0; i < absoluteOpaque.size(); i++)
            relativeOpaque.at(i) = absoluteOpaque.at(i);
    }
    /// else take into account previous object
    else {
        for (size_t i = 0; i < object->relativeOpaque.size(); i++)
            relativeOpaque.at(i) = object->relativeOpaque.at(i);
    }

}
