#ifndef OPTICAL_SIMULATION_TRANSPARENCY_H
#define OPTICAL_SIMULATION_TRANSPARENCY_H

#include "parameters.h"

/*
 * Class used to store 2D array of object transparency.
 */
class Transparency
{
public:
    Transparency();
    Transparency(ObjType objType, int XSize);           // EDGE, GAP or CIRCLE
    Transparency(dataT2D& field, int XSize, int YSize); // random field XSize*YSize
    virtual ~Transparency() {}
    void plot();

public:
    ObjType type;
    dataT2D opaque;
};


#endif //OPTICAL_SIMULATION_TRANSPARENCY_H
