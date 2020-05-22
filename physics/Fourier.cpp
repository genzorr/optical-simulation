#include "Fourier.h"

int FFT(int dir, int m, int twopm, complex *c)
{
    long nn,i,i1,j,k,i2,l,l1,l2;
    double c1,c2,t1,t2,u1,u2,z;
    complex t(0, 0);

    /* Calculate the number of points */
    nn = twopm;

    /* Do the bit reversal */
    i2 = nn >> 1;
    j = 0;
    for (i = 0; i < nn - 1; i++)
    {
        if (i < j)
        {
            t = c[i];
            c[i] = c[j];
            c[j] = t;
        }

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
        for (j = 0; j < l1; j++)
        {
            for (i = j; i < nn; i += l2)
            {
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
        for (i = 0; i < nn; i++)
            c[i] /= (double)nn;
    }

    return true;
}

int FFT2D(dataT2Dc &c, int nx, int ny, int dir)
{
    int m = 9, twopm = 512;

    /* Transform the columns */
    complex *carr = new complex[ny];

    for (int x = 0; x < nx; x++)
    {
        for (int y = 0; y < ny; y++) {
            carr[y] = c[x][y];
        }

        FFT(dir, m, twopm, carr);

        for (int y = 0; y < ny; y++) {
            c[x][y] = carr[y];
        }
    }
    delete [] carr;

    carr = new complex[nx];

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

    return true;
}


