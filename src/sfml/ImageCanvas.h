#ifndef OPTICAL_SIMULATION_IMAGECANVAS_H
#define OPTICAL_SIMULATION_IMAGECANVAS_H

#include "QSFMLCanvas.h"

/*
 * Subclass used to draw result image.
 */
class ImageCanvas : public QSFMLCanvas
{
Q_OBJECT
public:
    explicit ImageCanvas(QWidget* parent = nullptr) : QSFMLCanvas(parent) {}
    virtual ~ImageCanvas() override {}

private:
    // First init of widget.
    virtual void onInit();
    // Before widget update.
    virtual void onUpdate();
};


#endif //OPTICAL_SIMULATION_IMAGECANVAS_H
