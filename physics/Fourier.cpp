#include "Fourier.h"

const dataT eps = 0.000001;

bool isEqual(dataT a, dataT b)
{
    return (a < b - eps) and (a > b + eps);
}

complex GrinFunction(int x, int y, int z, dataT lambda)
{
    complex result(0, 0);

    dataT k = 2*M_PI/lambda;
    dataT k_2 = k*k;
    dataT x_2 = x*x;
    dataT y_2 = y*y;
    dataT z_2 = z*z;
    dataT kx1 = - k * z / sqrt(z_2+x_2);
    dataT kx2 = k * z / sqrt(z_2+(WindowXSize-x)*(WindowXSize-x));
    dataT ky1 = - k * z / sqrt(z_2+y_2);
    dataT ky2 = k * z / sqrt(z_2+(WindowYSize-y)*(WindowYSize-y));


    for (dataT kx = kx1; kx < kx2; kx += 10)
    {
        dataT kx_2 = kx*kx;
        for (dataT ky = ky1; ky < ky2; ky += 10)
        {
            dataT kz = sqrt(k_2 - kx_2 - ky*ky);
            dataT value = kx*x + ky*y + kz*z;
            result += (cos(value), sin(value));
        }
    }

    return result;
}

complex PointFieldTension(dataT2D &opaque, int x, int y, int z, dataT lambda)
{
    complex result(0, 0);

    for (int x1 = 0; x1 < WindowXSize; x1++)
    {
        for (int y1 = 0; y1 < WindowYSize; y1++)
        {
            if (!isEqual(opaque[x1][y1], 0.0))
                result += opaque[x1][y1] * GrinFunction(x-x1, y-y1, z, lambda);
        }
    }
}

void CountFieldIntensity(dataT2D &opaque, dataT2D &intensity, int z, dataT lambda)
{
    for (int x = 0; x < WindowXSize; x++)
    {
        for (int y = 0; y < WindowYSize; y++)
        {
            complex result = PointFieldTension(opaque, x, y, z, lambda);
            intensity[x][y] = std::abs(result);
        }
    }
}

