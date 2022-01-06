# Raster Window Example



This example shows how to create a minimal [QWindow](https://doc.qt.io/qt-5/qwindow.html) based application using [QPainter](https://doc.qt.io/qt-5/qpainter.html) for rendering.



## Application Entry Point

```c++
int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    RasterWindow window;
    window.show();

    return app.exec();
}
```

The entry point for a [QWindow](https://doc.qt.io/qt-5/qwindow.html) based application is the [QGuiApplication](https://doc.qt.io/qt-5/qguiapplication.html) class. It manages the GUI application's control flow and main settings. We pass the command line arguments which can be used to pick up certain system wide options.

From there, we go on to create our window instance and then call the [QWindow::show](https://doc.qt.io/qt-5/qwindow.html#show)() function to tell the windowing system that this window should now be made visible on screen.

Once this is done, we enter the application's event loop so the application can run.



## RasterWindow Declaration

```c++
#include <QtGui>

class RasterWindow : public QWindow
{
    Q_OBJECT
public:
    explicit RasterWindow(QWindow *parent = 0);

    virtual void render(QPainter *painter);

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;
    void exposeEvent(QExposeEvent *event) override;

private:
    QBackingStore *m_backingStore;
};
```

We first start by including the `<QtGui>` header. This means we can use all classes in the Qt GUI module. Classes can also be included individually if that is preferred.

The RasterWindow class subclasses [QWindow](https://doc.qt.io/qt-5/qwindow.html) directly and provides a constructor which allows the window to be a sub-window of another [QWindow](https://doc.qt.io/qt-5/qwindow.html). Parent-less QWindows show up in the windowing system as top-level windows.

The class declares a [QBackingStore](https://doc.qt.io/qt-5/qbackingstore.html) which is what we use to manage the window's back buffer for [QPainter](https://doc.qt.io/qt-5/qpainter.html) based graphics.

*The raster window is also reused in a few other examples and adds a few helper functions, like renderLater().*



## RasterWindow Implementation

```c++
RasterWindow::RasterWindow(QWindow *parent)
    : QWindow(parent)
    , m_backingStore(new QBackingStore(this))
{
    setGeometry(100, 100, 300, 200);
}
```

In the constructor we create the backingstore and pass it the window instance it is supposed to manage. We also set the initial window geometry.

```c++
void RasterWindow::exposeEvent(QExposeEvent *)
{
    if (isExposed())
        renderNow();
}
```

Shortly after calling [QWindow::show](https://doc.qt.io/qt-5/qwindow.html#show)() on a created window, the virtual function [QWindow::exposeEvent](https://doc.qt.io/qt-5/qwindow.html#exposeEvent)() will be called to notify us that the window's exposure in the windowing system has changed. The event contains the exposed sub-region, but since we will anyway draw the entire window every time, we do not make use of that.

The function [QWindow::isExposed](https://doc.qt.io/qt-5/qwindow.html#isExposed)() will tell us if the window is showing or not. We need this as the exposeEvent is called also when the window becomes obscured in the windowing system. If the window is showing, we call renderNow() to draw the window immediately. We want to draw right away so we can present the system with some visual content.

```c++
void RasterWindow::resizeEvent(QResizeEvent *resizeEvent)
{
    m_backingStore->resize(resizeEvent->size());
}
```

The resize event is guaranteed to be called prior to the window being shown on screen and will also be called whenever the window is resized while on screen. We use this to resize the back buffer, and defer rendering to the corresponding/following expose event.

```c++
void RasterWindow::renderNow()
{
    if (!isExposed())
        return;

    QRect rect(0, 0, width(), height());
    m_backingStore->beginPaint(rect);

    QPaintDevice *device = m_backingStore->paintDevice();
    QPainter painter(device);

    painter.fillRect(0, 0, width(), height(), QGradient::NightFade);
    render(&painter);
    painter.end();

    m_backingStore->endPaint();
    m_backingStore->flush(rect);
}
```

The renderNow function sets up what is needed for a [QWindow](https://doc.qt.io/qt-5/qwindow.html) to render its content using [QPainter](https://doc.qt.io/qt-5/qpainter.html). As obscured windows have will not be visible, we abort if the window is not exposed in the windowing system. This can for instance happen when another window fully obscures this window.

We start the drawing by calling [QBackingStore::beginPaint](https://doc.qt.io/qt-5/qbackingstore.html#beginPaint)() on the region we want to draw. Then we get the [QPaintDevice](https://doc.qt.io/qt-5/qpaintdevice.html) of the back buffer and create a [QPainter](https://doc.qt.io/qt-5/qpainter.html) to render to that paint device.

To void leaving traces from the previous rendering and start with a clean buffer, we fill the entire buffer with the color white. Then we call the virtual render() function which does the actual drawing of this window.

After drawing is complete, we call endPaint() to signal that we are done rendering and present the contents in the back buffer using [QBackingStore::flush](https://doc.qt.io/qt-5/qbackingstore.html#flush)().

```c++
void RasterWindow::render(QPainter *painter)
{
    painter->drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, QStringLiteral("QWindow"));
}
```

The render function contains the drawing code for the window. In this minial example, we only draw the string "[QWindow](https://doc.qt.io/qt-5/qwindow.html)" in the center.



## Rendering Asynchronously

```c++
void RasterWindow::renderLater()
{
    requestUpdate();
}
```

We went through a few places where the window needed to repainted immediately. There are some cases where this is not desirable, but rather let the application return to the event loop and schedule the repaint for later. We achieve this by requesting an update, using [QWindow::requestUpdate](https://doc.qt.io/qt-5/qwindow.html#requestUpdate)(), which will then be delivered when the system is ready to repaint.

```c++
bool RasterWindow::event(QEvent *event)
{
    if (event->type() == QEvent::UpdateRequest) {
        renderNow();
        return true;
    }
    return QWindow::event(event);
}
```

We reimplement the virtual [QObject::event](https://doc.qt.io/qt-5/qobject.html#event)() function to handle the update event. When the event comes in we call renderNow() to render the window right away.



