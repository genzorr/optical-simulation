#ifndef OPTICAL_SIMULATION_FOURIERCANVAS_H
#define OPTICAL_SIMULATION_FOURIERCANVAS_H

#include "Transparency.h"
#include "QSFMLCanvas.h"

class FourierCanvas : public QSFMLCanvas
{
Q_OBJECT
public:
    explicit FourierCanvas(QWidget* parent = nullptr) : QSFMLCanvas(parent) {}
    virtual ~FourierCanvas() override {}
    void setObject(Transparency* object) {resultObject = object;};

private:
    /// First init of widget.
    virtual void onInit();
    /// Before widget update.
    virtual void onUpdate();

private:
    Transparency* resultObject;
};


#endif //OPTICAL_SIMULATION_FOURIERCANVAS_H
