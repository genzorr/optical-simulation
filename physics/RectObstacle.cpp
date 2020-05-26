#include "RectObstacle.h"

void RectObstacle::Update(int sizeX, int sizeY) {
    for (int i = 0; i < WindowXSize; i++)
    {
        absoluteOpaque[i].resize(WindowYSize);
        relativeOpaque[i].resize(WindowYSize);
        std::fill(absoluteOpaque[i].begin(), absoluteOpaque[i].end(), 0);
        std::fill(relativeOpaque[i].begin(), relativeOpaque[i].end(), 0);

        fourierImage[i].resize(WindowYSize);
        std::fill(fourierImage[i].begin(), fourierImage[i].end(), complex(0, 0));
    }

    int left = (int)((WindowXSize - sizeX) / 2);
    int top = (int)((WindowYSize - sizeY) / 2);

    for (int x = left; x < (WindowXSize - left); x++)
        {
            for (int y = top; y < (WindowYSize - top); y++)
            {
                absoluteOpaque[x][y] = 1;
                image.setPixel(x, y, sf::Color(255, 0, 0));
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

void RectObstacle::UpdateSize(int sizeX, int sizeY) {
    Update(sizeX, sizeY);
    CreateImage(5, 500E-9, 10E-6);
}
