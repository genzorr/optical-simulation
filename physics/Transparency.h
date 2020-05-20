#ifndef OPTICAL_SIMULATION_TRANSPARENCY_H
#define OPTICAL_SIMULATION_TRANSPARENCY_H

#include <SFML/Graphics.hpp>
#include "parameters.h"

/*
 * Class used to store 2D array of object transparency.
 */
class Transparency : public QObject
{
Q_OBJECT
public:
    Transparency();
    Transparency(const Transparency& object);
    Transparency(ObjType objType, int XSize);           // EDGE, GAP or CIRCLE
    Transparency(dataT2D& field, int XSize, int YSize); // random field XSize*YSize
    virtual ~Transparency() {}

    void init(const Transparency &object);
    void OpaquetoImage();

public:
    ObjType type;
    dataT2D opaque;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
};

typedef std::vector<Transparency> ObjHolder;


#endif //OPTICAL_SIMULATION_TRANSPARENCY_H
