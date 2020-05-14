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
    Transparency(ObjType objType, int XSize);             // EDGE, GAP or CIRCLE
    Transparency(dataT** field, int XSize, int YSize);    // random field Xsize*Ysize
    void plot();

public:
    ObjType type;
    dataT2D opaque;
};


#endif //OPTICAL_SIMULATION_TRANSPARENCY_H
