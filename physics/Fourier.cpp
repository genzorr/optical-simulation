#include "Fourier.h"

const dataT eps = 0.000001;

bool isEqual(dataT a, dataT b)
{
    return (fabs(a-b) < eps);
//    return (a < b - eps) or (a > b + eps);
}

complex GrinFunction(int x, int y, int z, dataT lambda)
{
    complex result(0, 0);

    dataT k = 2*M_PI/lambda;
    dataT k_2 = k*k;
    dataT x_2 = x*x;
    dataT y_2 = y*y;
    dataT z_2 = z*z;

    dataT xOther = WindowXSize - x;
    dataT yOther = WindowYSize - y;
    dataT kx1 = - k * x / sqrt(z_2+x_2);
    dataT kx2 = k * xOther / sqrt(z_2+xOther*xOther);
    dataT ky1 = - k * y / sqrt(z_2+y_2);
    dataT ky2 = k * yOther / sqrt(z_2+yOther*yOther);


    for (dataT kx = kx1; kx < kx2; kx += 100000)
    {
        dataT kx_2 = kx*kx;
        for (dataT ky = ky1; ky < ky2; ky += 100000)
        {
            dataT kz_2 = k_2 - kx_2 - ky*ky;
            if (kz_2 < 0.0)
                continue;
            dataT kz = sqrt(kz_2);
            dataT value = kx*x + ky*y + kz*z;
            result += (cos(value), -sin(value));
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


int FFT(int dir, int m, int twopm, complex *c)
{
    long nn,i,i1,j,k,i2,l,l1,l2;
    double c1,c2,tx,ty,t1,t2,u1,u2,z;
    complex t(0, 0);

    /* Calculate the number of points */
    nn = twopm;

    /* Do the bit reversal */
    i2 = nn >> 1;
    j = 0;
    for (i = 0; i < nn - 1; i++)
    {
        if (i < j)
            std::swap(c[i], c[j]);

        k = i2;
        while (k <= j)
        {
            j -= k;
            k >>= 1;
        }
        j += k;
    }

    /* Compute the FFT */
    c1 = -1.0;
    c2 = 0.0;
    l2 = 1;
    for (l = 0; l < m; l++) {
        l1 = l2;
        l2 <<= 1;
        u1 = 1.0;
        u2 = 0.0;
        for (j = 0; j < l1; j++) {
            for (i = j; i < nn; i += l2) {
                i1 = i + l1;
                t1 = u1 * c[i1].real() - u2 * c[i1].imag();
                t2 = u1 * c[i1].imag() + u2 * c[i1].real();
                c[i1] = c[i] - complex(t1, t2);
                c[i] += complex(t1, t2);
            }
            z =  u1 * c1 - u2 * c2;
            u2 = u1 * c2 + u2 * c1;
            u1 = z;
        }
        c2 = sqrt((1.0 - c1) / 2.0);
        if (dir == 1)
            c2 = -c2;
        c1 = sqrt((1.0 + c1) / 2.0);
    }

    /* Scaling for forward transform */
    if (dir == 1)
    {
        for ( i = 0;i < nn; i++)
            c[i] /= nn;
    }

    return true;
}

int FFT2D(dataT2Dc &c, int nx, int ny, int dir)
{
    int m = 9, twopm = 512;

    complex *carr = new complex[nx];

    /* Transform the rows */
    for (int y = 0; y < ny; y++)
    {
        for (int x = 0; x < nx; x++)
            carr[x] = c[x][y];

        FFT(dir, m, twopm, carr);

        for (int x = 0; x < nx; x++)
            c[x][y] = carr[x];
    }
    delete [] carr;

    /* Transform the columns */
    carr = new complex[ny];

    for (int x = 0; x < nx; x++)
    {
        for (int y = 0; y < ny; y++)
            carr[y] = c[x][y];

        FFT(dir, m, twopm, carr);

        for (int y = 0; y < ny; y++)
            c[x][y] = carr[y];
    }
    delete [] carr;

    return true;
}


