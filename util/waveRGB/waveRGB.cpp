#include "waveRGB.h"
#include "cmath"


sf::Color WaveRGB::Calc(double len) {
    if(len < LEN_MIN || len > LEN_MAX)
        return sf::Color::Black;

    len -= LEN_MIN;
    auto index = (int)floor(len / LEN_STEP);
    auto offset = len - LEN_STEP * index;

    auto x = Interpolate(X, index, offset);
    auto y = Interpolate(Y, index, offset);
    auto z = Interpolate(Z, index, offset);

    auto m = MATRIX_SRGB_D65;

    auto r = m[0] * x + m[1] * y + m[2] * z;
    auto g = m[3] * x + m[4] * y + m[5] * z;
    auto b = m[6] * x + m[7] * y + m[8] * z;

    r = Clip(GammaCorrect_sRGB(r));
    g = Clip(GammaCorrect_sRGB(g));
    b = Clip(GammaCorrect_sRGB(b));


    return sf::Color (255*r, 255*g, 255*b);
}

double WaveRGB::Interpolate(const double* values, int index, double offset) {
    if(offset == 0)
        return values[index];

    auto x0 = index * LEN_STEP;
    auto x1 = x0 + LEN_STEP;
    auto y0 = values[index];
    auto y1 = values[1 + index];

    return y0 + offset * (y1 - y0) / (x1 - x0);
}

double WaveRGB::GammaCorrect_sRGB(double c) {
        if(c <= 0.0031308)
            return 12.92 * c;

        auto a = 0.055;
        return (1 + a) * pow(c, 1 / 2.4) - a;
}

double WaveRGB::Clip(double c) {
    if(c < 0)
        return 0;
    if(c > 1)
        return 1;
    return c;
}