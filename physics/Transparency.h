#ifndef OPTICAL_SIMULATION_TRANSPARENCY_H
#define OPTICAL_SIMULATION_TRANSPARENCY_H

#include <SFML/Graphics.hpp>
#include "parameters.h"

#define DEFAULT_WAVELEN 500

///
/// Class used to store 2D array of object transparency.
///
class Transparency : public QObject
{
Q_OBJECT
public:
    Transparency();
    Transparency(const Transparency *object);   /// construct object from given
    Transparency(ObjType objType, int size);           /// EDGE, GAP or CIRCLE
    Transparency(dataT2D& field, int XSize, int YSize); /// random field XSize*YSize
    virtual ~Transparency() {}

    void UpdateArrays(const Transparency *object = nullptr, dataT value = 0);    /// to reset/fill from other object opaque and fourier arrays
    void UpdateImages(const Transparency *object = nullptr, bool recalc = false);    /// perform updates on 2 images, textures and sprites

    void Init(const Transparency *object);
    void UpdateSize(int size);  /// fills arrays, updates all images

    void CopyOpaqueFourier();
    void setRelativeOpaque(const Transparency *object = nullptr);
    void relativeOpaqueImage();
    void CreatePreview();   /// called on update, but might be manually called for specific purposes

    void FourierNormalize();
    void FourierTranslateNormalize();
    void CountFourierImage(bool resetFourier = false, bool translate = false);           /// that and next performs ONLY fourier array fill
    void CountInverseFourierImage();

    void CreateFourierImage();          /// that counts fourier and fills the fourierImage
    void CreateImage();
    void CountImage(dataT z, dataT scale);

public slots:
    void Update(int size = -1);

public:
    double position;                /// Distance from light emitter
    ObjType type;
    dataT2D absoluteOpaque;         /// Characteristic of the object itself  1 - transparent 0 - not transparent
    dataT2D relativeOpaque;         /// Relative to falling light            1 - transparent 0 - not transparent
    dataT2Dc fourier;

    sf::Color pixelColor;
    dataT lambda;

    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    /// Everything for preview
    sf::Image imagePreview;
    sf::Texture texturePreview;
    sf::Sprite spritePreview;

    /// Fourier image
    sf::Image imageFourier;
    sf::Texture textureFourier;
    sf::Sprite spriteFourier;
};

typedef std::vector<Transparency> ObjHolder;


#endif //OPTICAL_SIMULATION_TRANSPARENCY_H
