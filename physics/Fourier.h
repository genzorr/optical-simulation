#ifndef OPTICAL_SIMULATION_FOURIER_H
#define OPTICAL_SIMULATION_FOURIER_H

#include "parameters.h"

complex GrinFunction(int x, int y, int z, dataT lambda);
complex PointFieldTension(dataT2D &opaque, int x, int y, int z, dataT lambda);
void CountFieldIntensity(dataT2D &opaque, dataT2D &intensity, int z, dataT lambda);

#endif //OPTICAL_SIMULATION_FOURIER_H
