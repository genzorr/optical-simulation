#ifndef OPTICAL_SIMULATION_QSFMLCANVAS_H
#define OPTICAL_SIMULATION_QSFMLCANVAS_H

#include <QWidget>
#include <QTimer>
#include <SFML/Graphics.hpp>

///
/// QSFMLCanvas
/// Class, inherited from QWidget and RenderWindow in order to provide Qt-SFML interaction.
/// @param parent       QWidget where SFML window will be placed
/// @param frameTime    dTime for widget to be repainted
///
class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
Q_OBJECT
public:
    explicit QSFMLCanvas(QWidget* parent = nullptr, uint frameTime = 50);
    virtual ~QSFMLCanvas() {}

protected:
    /// First init of widget.
    virtual void onInit();
    /// Before widget update.
    virtual void onUpdate();
    /// Resizes widget and SFML RenderWindow
    virtual void resizeEvent(QResizeEvent *event);

private:
    /// Returns Qt's paint engine.
    virtual QPaintEngine* paintEngine() const override;
    /// For open and close, used on first init.
    virtual void showEvent(QShowEvent*) override;
    /// Repaints widget.
    virtual void paintEvent(QPaintEvent*) override;

private slots:
    /// Used to repaint widget.
    void onTimeout();


private:
    QTimer m_timer;         /// used to repaint widget with %frameTime% interval
    bool   m_initialized;   /// to be set on init
};

#endif //OPTICAL_SIMULATION_QSFMLCANVAS_H
