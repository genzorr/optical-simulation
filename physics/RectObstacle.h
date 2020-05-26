#pragma once

#include "Transparency.h"

class RectObstacle : public Transparency {
public:
    void Update(int sizeX, int sizeY);
    void UpdateSize(int sizeX, int sizeY);
};
