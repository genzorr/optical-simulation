#ifndef OPTICAL_SIMULATION_PARAMETERS_H
#define OPTICAL_SIMULATION_PARAMETERS_H

#include <vector>

typedef float dataT;
typedef std::vector<std::vector<dataT>> dataT2D;

// Type of the transparency object.
enum ObjType
{
    NO = 0,
    EDGE,
    GAP,
    CIRCLE
};

extern int WindowXSize;
extern int WindowYSize;

#endif //OPTICAL_SIMULATION_PARAMETERS_H
