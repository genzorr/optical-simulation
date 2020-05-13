#include "QSFMLCanvas.h"

#include <string>

#include <QPixmap>
#include <QByteArray>
#include <QBuffer>
#include <QDebug>


QSFMLCanvas::QSFMLCanvas(QWidget* parent, uint frameTime) :
    QWidget(parent),
    sf::RenderWindow(sf::VideoMode(10, 10), "this title", sf::Style::Default, sf::ContextSettings(24)),
    m_initialized(false)
{
    // Settings needed to paint to widget directly.
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    setFocusPolicy(Qt::StrongFocus);

    m_timer.setInterval(frameTime);
}

void QSFMLCanvas::onInit()
{
    resize(parentWidget()->size());
}

void QSFMLCanvas::onUpdate()
{
    resize(parentWidget()->size());
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    // Return NULL here to block Qt to paint something by itself!!
    return nullptr;
}

void QSFMLCanvas::showEvent(QShowEvent*)
{
    // First widget init.
    if (!m_initialized)
    {
        // Create window and pass window ID where to paint.
        RenderWindow::create(winId());

        // Default widget init.
        onInit();

        // Update timer setup.
        connect(&m_timer, &QTimer::timeout, this, &QSFMLCanvas::onTimeout);
        m_timer.start();

        m_initialized = true;
    }
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
    // Invoked when this->repaint() or this->update() used.

    // Do some specific stuff.
    onUpdate();

    // Display repainted window.
    display();
}

void QSFMLCanvas::onTimeout()
{
    update();
}