#ifndef OPTICAL_SIMULATION_FIELDCANVAS_H
#define OPTICAL_SIMULATION_FIELDCANVAS_H

#include "QSFMLCanvas.h"

class Transparency;

/*
 * Subclass used to draw optical system field.
 */
class FieldCanvas : public QSFMLCanvas
{
Q_OBJECT
public:
    explicit FieldCanvas(QWidget* parent = nullptr) : QSFMLCanvas(parent) {}
    virtual ~FieldCanvas() override {}
    void setObject(Transparency* object) {resultObject = object;};

private:
    // First init of widget.
    virtual void onInit();
    // Before widget update.
    virtual void onUpdate();

private:
    Transparency* resultObject;
};


#endif //OPTICAL_SIMULATION_FIELDCANVAS_H
