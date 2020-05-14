#ifndef OPTICAL_SIMULATION_TRANSPARENCY_H
#define OPTICAL_SIMULATION_TRANSPARENCY_H

#include <SFML/Graphics.hpp>
#include "parameters.h"

/*
 * Class used to store 2D array of object transparency.
 */
class Transparency : public QObject
{
public:
    Transparency();
    Transparency(ObjType objType, int XSize);           // EDGE, GAP or CIRCLE
    Transparency(dataT2D& field, int XSize, int YSize); // random field XSize*YSize
    virtual ~Transparency() {}
    void plot(sf::RenderWindow& window);

public:
    ObjType type;
    dataT2D opaque;
    sf::Sprite sprite;
};


#endif //OPTICAL_SIMULATION_TRANSPARENCY_H
