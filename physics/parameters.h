#ifndef OPTICAL_SIMULATION_PARAMETERS_H
#define OPTICAL_SIMULATION_PARAMETERS_H

#include <vector>
#include <QObject>
#include <QWidget>
#include <complex>

typedef double dataT;
typedef std::complex<dataT> complex;
typedef std::vector<std::vector<dataT>> dataT2D;
typedef std::vector<std::vector<complex>> dataT2Dc;

// Type of the transparency object.
enum ObjType
{
    NO = 0,
    EDGE,
    GAP,
    CIRCLE,
    SQUARE
};

extern const int OBJECT_CNT;

extern int WindowXSize;
extern int WindowYSize;

#endif //OPTICAL_SIMULATION_PARAMETERS_H
