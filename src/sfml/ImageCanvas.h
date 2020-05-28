#ifndef OPTICAL_SIMULATION_IMAGECANVAS_H
#define OPTICAL_SIMULATION_IMAGECANVAS_H

#include "parameters.h"
#include "QSFMLCanvas.h"
#include "Transparency.h"

///
/// Subclass used to draw result image.
///
class ImageCanvas : public QSFMLCanvas
{
Q_OBJECT
public:
    explicit ImageCanvas(QWidget* parent = nullptr);
    virtual ~ImageCanvas() override {}
    Transparency* getObject();

private:
    /// First init of widget.
    virtual void onInit();
    /// Before widget update.
    virtual void onUpdate();
    /// Custom resizeEvent.
    virtual void resizeEvent(QResizeEvent *event);

public:
    Transparency resultObject;
    ObjHolder objHolder;

public slots:
    void UpdateLambda(int lambda, int size = -1);
    void UpdateDistance(int distance, int size = -1);

    void MorphToGap();
    void MorphToSquare();
    void MorphToLattice();
    void MorphToGrid();
};


#endif //OPTICAL_SIMULATION_IMAGECANVAS_H
