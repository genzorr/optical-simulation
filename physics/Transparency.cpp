#include <algorithm>
#include "Transparency.h"

Transparency::Transparency() :
    type(NO)
{
    opaque.resize(WindowXSize);
    for (auto& item: opaque) {
        item.resize(WindowYSize);
        std::fill(item.begin(), item.end(), 0);
    }
}

Transparency::Transparency(ObjType objType, int XSize) :
        type(objType)
{
    opaque.resize(WindowXSize);
    for (auto& item: opaque) {
        item.resize(WindowYSize);
        std::fill(item.begin(), item.end(), 0);
    }

    if (objType == EDGE)
    {
        int edgeXCoordinate = (WindowXSize / 2) - XSize;
        for (int x = 0; x < WindowXSize; x++)
        {
            for (int y = 0; y < WindowYSize; y++)
            {
                if (x < edgeXCoordinate)
                    std::fill(opaque[x].begin(), opaque[x].end(), 0);
                else
                    std::fill(opaque[x].begin(), opaque[x].end(), 1);
            }
        }
    }
}