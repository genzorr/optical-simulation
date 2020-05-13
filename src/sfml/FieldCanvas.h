#ifndef OPTICAL_SIMULATION_FIELDCANVAS_H
#define OPTICAL_SIMULATION_FIELDCANVAS_H

#include "QSFMLCanvas.h"

/*
 * Subclass used to draw optical system field.
 */
class FieldCanvas : public QSFMLCanvas
{
Q_OBJECT
public:
    explicit FieldCanvas(QWidget* parent = nullptr) : QSFMLCanvas(parent) {}
    virtual ~FieldCanvas() override {}

private:
    // First init of widget.
    virtual void onInit();
    // Before widget update.
    virtual void onUpdate();
};


#endif //OPTICAL_SIMULATION_FIELDCANVAS_H
