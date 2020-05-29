#include <algorithm>
#include <QDebug>
#include "Transparency.h"
#include "Fourier.h"
#include "../util/waveRGB/waveRGB.h"

Transparency::Transparency() : type(NO)
{
    /// Init pixel color.
    lambda = LAMBDA;
    pixelColor = WaveRGB::Calc(LAMBDA);

    UpdateArrays(nullptr, 1);

    /// Initialize images.
    UpdateImages();

    Update(INIT_SIZE);
}

Transparency::Transparency(ObjType objType, int size) : type(objType)
{
    lambda = LAMBDA;
    pixelColor = WaveRGB::Calc(LAMBDA);

    UpdateArrays(nullptr, 1);
    UpdateImages();

    Update(size);
}

Transparency::Transparency(dataT2D &field, int XSize, int YSize)
{
    // TODO: make initialization
    lambda = LAMBDA;
    pixelColor = WaveRGB::Calc(LAMBDA);
}

Transparency::Transparency(const Transparency *object)
{
    lambda = LAMBDA;
    pixelColor = WaveRGB::Calc(LAMBDA);

    UpdateArrays(object);
    UpdateImages(object);

    Update(INIT_SIZE);
}

void Transparency::UpdateArrays(const Transparency *object, dataT value)
{
    relativeOpaque.resize(WindowXSize);
    absoluteOpaque.resize(WindowXSize);
    fourier.resize(WindowXSize);

    if (object == nullptr)
    {
        for (int i = 0; i < WindowXSize; i++)
        {
            relativeOpaque[i].resize(WindowYSize);
            std::fill(relativeOpaque[i].begin(), relativeOpaque[i].end(), value);

            absoluteOpaque[i].resize(WindowYSize);
            std::fill(absoluteOpaque[i].begin(), absoluteOpaque[i].end(), value);

            fourier[i].resize(WindowYSize);
            std::fill(fourier[i].begin(), fourier[i].end(), complex(value, 0));
        }
    }
    else
    {
        relativeOpaque.resize(0);
        absoluteOpaque.resize(0);
        fourier.resize(0);
        for (size_t i = 0; i < object->relativeOpaque.size(); i++)
            relativeOpaque.push_back(object->relativeOpaque[i]);

        for (size_t i = 0; i < object->absoluteOpaque.size(); i++)
            absoluteOpaque.push_back(object->absoluteOpaque[i]);

        for (size_t i = 0; i < object->fourier.size(); i++)
            fourier.push_back(object->fourier[i]);
    }
}

void Transparency::UpdateImages(const Transparency *object, bool recalc)
{
    /// Image.
    const sf::Rect rect(0,0, WindowXSize, WindowYSize);
    image.create(WindowXSize, WindowYSize, sf::Color::White);
    if (object != nullptr)
        image.copy(object->image, 0, 0, rect, true);

    texture.create(WindowXSize, WindowYSize);
    texture.update(image);
    sprite.setTexture(texture, true); /// don't forget to reset sprite's rect!!

    /// Preview.
    imagePreview.create(WindowXSize, WindowYSize, sf::Color::White);
    if (object != nullptr)
        imagePreview.copy(object->imagePreview, 0, 0, rect, true);

    texturePreview.create(WindowXSize, WindowYSize);
    if (recalc) CreatePreview();
    texturePreview.update(imagePreview);
    spritePreview.setTexture(texturePreview, true);

    /// Fourier image.
    imageFourier.create(WindowXSize, WindowYSize, sf::Color::White);
    if (object != nullptr)
        imageFourier.copy(object->imageFourier, 0, 0, rect, true);

    textureFourier.create(WindowXSize, WindowYSize);
    if (recalc) CreateFourierImage();
    textureFourier.update(imageFourier);
    spriteFourier.setTexture(textureFourier, true);
//    spriteFourier.setOrigin(WindowXSize_2, WindowYSize_2);
//    qDebug() << spriteFourier.getOrigin().x;
}

void Transparency::Init(const Transparency *object)
{
    type = object->type;
    lambda = object->lambda;
    pixelColor = object->pixelColor;

    UpdateArrays(object);
    UpdateImages(object);

    Update(INIT_SIZE);
}

void Transparency::UpdateSize(int size)
{
    lambda = LAMBDA;
    pixelColor = WaveRGB::Calc(LAMBDA);

    if (size != -1)
    {
        UpdateArrays(nullptr, 0);

        if (type == GAP)
        {
            int left = (int) ((WindowXSize - size) / 2);
            for (int x = left; x < WindowXSize - left; x++) {
                std::fill(absoluteOpaque[x].begin(), absoluteOpaque[x].end(), 1.0);
                for (int y = 0; y < WindowYSize; y++)
                    image.setPixel(x, y, pixelColor);
            }
        }
        else if (type == SQUARE)
        {
            int left = (int) ((WindowXSize - size) / 2);
            int top = (int) ((WindowYSize - size) / 2);

            for (int x = left; x < (WindowXSize - left); x++) {
                for (int y = top; y < (WindowYSize - top); y++) {
                    absoluteOpaque[x][y] = 1;
                    image.setPixel(x, y, pixelColor);
                }
            }
        }
        else if (type == LATTICE)
        {
            int lineWidth = 2*3;    /// Must be 2*k, k = 1, 2, ...
            int left = (int)((WindowXSize - lineWidth/2) / 2);
            while (left + lineWidth < WindowXSize) {
                for (int x = left; x < left + lineWidth; x++) {
                    std::fill(absoluteOpaque[x].begin(), absoluteOpaque[x].end(), 1.0);
                    for (int y = 0; y < WindowYSize; y++)
                        image.setPixel(x, y, pixelColor);
                }
                left += lineWidth + size;
            }


            left = (int)((WindowXSize - lineWidth/2) / 2) - lineWidth - size;
            while (left > 0) {
                for (int x = left; x < left + lineWidth; x++) {
                    std::fill(absoluteOpaque[x].begin(), absoluteOpaque[x].end(), 1.0);
                    for (int y = 0; y < WindowYSize; y++)
                        image.setPixel(x, y, pixelColor);
                }
                left -= lineWidth + size;
            }

        }
        else if (type == GRID)
        {
            float inverted = 0;   /// Set to 0 or 1.0 to invert the grid
            int lineWidth = 2*1;    /// Must be 2*k, k = 1, 2, ...
            for (int i = 0; i < WindowXSize; i++)
            {
                absoluteOpaque[i].resize(WindowXSize);
                relativeOpaque[i].resize(WindowXSize);
                std::fill(absoluteOpaque[i].begin(), absoluteOpaque[i].end(), inverted);
                std::fill(relativeOpaque[i].begin(), relativeOpaque[i].end(), inverted);

                fourier[i].resize(WindowXSize);
                std::fill(fourier[i].begin(), fourier[i].end(), complex(0, 0));
            }



            ///Draw vertical lines
            int left = (int)((WindowXSize - lineWidth/2) / 2);
            while (left + lineWidth < WindowXSize) {
                for (int x = left; x < left + lineWidth; x++) {
                    std::fill(absoluteOpaque[x].begin(), absoluteOpaque[x].end(), 1.0 - inverted);
                    for (int y = 0; y < WindowYSize; y++)
                        image.setPixel(x, y, pixelColor);
                }
                left += lineWidth + size;
            }


            left = (int)((WindowXSize - lineWidth/2) / 2) - lineWidth - size;
            while (left > 0) {
                for (int x = left; x < left + lineWidth; x++) {
                    std::fill(absoluteOpaque[x].begin(), absoluteOpaque[x].end(), 1.0 - inverted);
                    for (int y = 0; y < WindowYSize; y++)
                        image.setPixel(x, y, pixelColor);
                }
                left -= lineWidth + size;
            }


            ///Draw horizontal lines
            int up = (int)((WindowXSize - lineWidth/2) / 2);
            while (up + lineWidth < WindowXSize) {
                for (int x = up; x < up + lineWidth; x++) {
                    for (int i = 0; i < WindowXSize; i++) {
                        absoluteOpaque[i][x] = 1.0 - inverted;
                    }

                    for (int y = 0; y < WindowYSize; y++)
                        image.setPixel(x, y, pixelColor);
                }
                up += lineWidth + size;
            }


            up = (int)((WindowXSize - lineWidth/2) / 2) - lineWidth - size;
            while (up > 0) {
                for (int x = up; x < up + lineWidth; x++) {
                    for (int i = 0; i < WindowXSize; i++) {
                        absoluteOpaque[i][x] = 1.0 - inverted;
                    }

                    for (int y = 0; y < WindowYSize; y++)
                        image.setPixel(x, y, pixelColor);
                }
                up -= lineWidth + size;
            }

        }
    }

    setRelativeOpaque();

    UpdateImages(nullptr, true);
}

void Transparency::CopyOpaqueFourier()
{
    setRelativeOpaque();
    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
            fourier[x][y] = complex(255 * relativeOpaque[x][y], 0);
    }
}

void Transparency::relativeOpaqueImage() {
    if ((image.getSize().x != WindowXSize) or (image.getSize().y != WindowYSize))
        image.create(WindowXSize, WindowYSize, sf::Color::Black);

    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            sf::Color pixel = pixelColor;
            pixel.r = (sf::Uint8)(pixel.r * relativeOpaque[x][y]);
            pixel.g = (sf::Uint8)(pixel.g * relativeOpaque[x][y]);
            pixel.b = (sf::Uint8)(pixel.b * relativeOpaque[x][y]);
            imagePreview.setPixel(x, y, pixel);
        }
    }

    texture.create(WindowXSize, WindowYSize);
    texture.update(image);
    sprite.setTexture(texture, true);
}

void Transparency::CreatePreview()
{
    if ((imagePreview.getSize().x != WindowXSize) or (imagePreview.getSize().y != WindowYSize))
        imagePreview.create(WindowXSize, WindowYSize, sf::Color::Black);

    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            //sf::Color pixel = pixelColor;
            sf::Color pixel = sf::Color::White;
            pixel.r = (sf::Uint8)(pixel.r * relativeOpaque[x][y]);
            pixel.g = (sf::Uint8)(pixel.g * relativeOpaque[x][y]);
            pixel.b = (sf::Uint8)(pixel.b * relativeOpaque[x][y]);
            imagePreview.setPixel(x, y, pixel);
        }
    }

    texturePreview.create(WindowXSize, WindowYSize);
    texturePreview.update(imagePreview, WindowXSize, WindowYSize);
    spritePreview.setTexture(texturePreview, true);
}

void Transparency::CountFourierImage(bool resetFourier, bool normalize)
{
    if (resetFourier) CopyOpaqueFourier();
    FFT2D(fourier, WindowXSize, WindowYSize, 1);
    FourierTranslate();

    if (normalize)  /// to plot fourierImage
        FourierNormalize();
}

void Transparency::CountInverseFourierImage()
{
    FourierTranslate();
    FFT2D(fourier, WindowXSize, WindowYSize, -1);
    FourierNormalize();
}

void Transparency::FourierTranslate()
{
    dataT2Dc copy(WindowXSize);
    for (int x = 0; x < WindowXSize; x++)
    {
        copy[x].resize(WindowYSize);
        for (int y = 0; y < WindowYSize; y++)
            copy[x][y] = fourier[x][y];
    }

    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
//            int newx = (x < WindowXSize_2) ? (WindowXSize_2 - x - 1) : (WindowXSize + WindowXSize_2 - x - 1);
//            int newy = (y < WindowYSize_2) ? (WindowYSize_2 - y - 1) : (WindowYSize + WindowYSize_2 - y - 1);
            int newx = (x < WindowXSize_2) ? (x + WindowXSize_2) : (x - WindowXSize_2);
            int newy = (y < WindowYSize_2) ? (y + WindowYSize_2) : (y - WindowYSize_2);

            fourier[x][y] = copy[newx][newy];
        }
    }

}

void Transparency::CreateFourierImage()
{
    if ((imageFourier.getSize().x != WindowXSize) or (imageFourier.getSize().y != WindowYSize))
        imageFourier.create(WindowXSize, WindowYSize, sf::Color::Black);

    CountFourierImage(true, true);

//    dataT max = 0;
//    dataT2D I(WindowXSize);
//    for (int x = 0; x < WindowXSize; x++)
//    {
//        I[x].resize(WindowYSize);
//        for (int y = 0; y < WindowYSize; y++)
//        {
//            dataT value = std::abs(fourier[x][y]) * std::abs(fourier[x][y]);
//            I[x][y] = value;
//            if (value > max)
//                max = value;
//        }
//    }

    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            complex value = fourier[x][y];
            dataT intense = std::abs(value);

            dataT pixelValue = (dataT)std::min(int(intense), 255) / 255.f;
//            dataT value = I[x][y] / max;
//            dataT pixelValue = value;

            sf::Color pixel = pixelColor;
            pixel.r = (sf::Uint8)(pixel.r * pixelValue);
            pixel.g = (sf::Uint8)(pixel.g * pixelValue);
            pixel.b = (sf::Uint8)(pixel.b * pixelValue);

            imageFourier.setPixel(x, y, pixel);
        }
    }

    textureFourier.create(WindowXSize, WindowYSize);
    textureFourier.update(imageFourier);

    /// Scale fourier image.
    spriteFourier.setScale(1.f, 1.f);
    spriteFourier.setTexture(textureFourier, true);
    spriteFourier.scale(sf::Vector2f((float)LAMBDA / 400, (float)LAMBDA / 400));
}

void Transparency::CountImage(dataT z, dataT scale)
{
    CountFourierImage(true, false);

    dataT lambda_ = (double)(lambda) * 1E-9;
//    dataT z_2 = z*z; // m^2
//    dataT k_z_2 = z_2 * 2 * M_PI / lambda_; // m

    dataT k = 2 * M_PI;
    dataT k_2 = k*k;
    dataT scale_2 = scale*scale;

    /// Iterate through all x y and apply z offset like complex exponent.
    for (int x = -WindowXSize_2; x < WindowXSize_2; x++)
    {
        dataT x_2 = x * x * scale_2;
        for (int y = -WindowYSize_2; y < WindowYSize_2; y++)
        {
//            dataT value = - k_z_2 * sqrt(x_2 + y*y*scale_2 + z_2);

            dataT k_x = M_PI * x / (256);
            dataT k_y = M_PI * y / (256);
            dataT k_z = sqrt(k_2 - k_x*k_x - k_y*k_y);
            dataT value = k_z * z / lambda_;

            complex exp(cos(value), sin(value));
            fourier[x + WindowXSize_2][y + WindowYSize_2] *= exp;
        }
    }

    CountInverseFourierImage();
    CreateImage();
}

void Transparency::CreateImage()
{
    if ((image.getSize().x != WindowXSize) or (image.getSize().y != WindowYSize))
        image.create(WindowXSize, WindowYSize, sf::Color::Black);

//    dataT max = 0;
//    dataT2D I(WindowXSize);
//    for (int x = 0; x < WindowXSize; x++)
//    {
//        I[x].resize(WindowYSize);
//        for (int y = 0; y < WindowYSize; y++)
//        {
//            dataT value = std::abs(fourier[x][y]) * std::abs(fourier[x][y]);
//            I[x][y] = value;
//            if (value > max)
//                max = value;
//        }
//    }

    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            complex value = fourier[x][y];
            dataT intense = std::abs(value);

            dataT pixelValue = (dataT)std::min(int(intense), 255) / 255.f;
//            dataT value = I[x][y] / max;
//            dataT pixelValue = value;

            sf::Color pixel = pixelColor;
            pixel.r = (sf::Uint8)(pixel.r * pixelValue);
            pixel.g = (sf::Uint8)(pixel.g * pixelValue);
            pixel.b = (sf::Uint8)(pixel.b * pixelValue);

            image.setPixel(x, y, pixel);
        }
    }

    texture.create(WindowXSize, WindowYSize);
    texture.update(image);
    sprite.setTexture(texture, true);
}

void Transparency::FourierNormalize()
{
    dataT max = 0;
    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
//            fourier[x][y] *= fourier[x][y];
            dataT value = std::abs(fourier[x][y]);
            if (value > max)
                max = value;
        }
    }

    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            fourier[x][y] = 255.0 * fourier[x][y] / max;
        }
    }
}

void Transparency::Update(int size)
{
    if (size != -1) INIT_SIZE = size;
    UpdateSize(size);

    dataT distMeters = (dataT)DIST / 1;
    CountImage(distMeters, 1E-3);
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
