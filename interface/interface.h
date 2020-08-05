#ifndef OPTICAL_SIMULATION_INTERFACE_H
#define OPTICAL_SIMULATION_INTERFACE_H

#include <QtCore/QTimer>
#include "../interface/ui_interface.h"

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow();
    ~MainWindow() {};

private:
    void resizeEvent(QResizeEvent* event);
    void moveEvent(QMoveEvent* event);
private slots:
    // To deal with resize properly.
    void resizeDone();

private:
    QTimer resizeTimer;
    bool m_resizeDone;
};

#endif //OPTICAL_SIMULATION_INTERFACE_H
