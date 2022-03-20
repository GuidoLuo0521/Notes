#ifndef SLICINGOBJECT_H
#define SLICINGOBJECT_H

#include "common.h"


class Window
{
public:
    Window() : m_name("window") {  cout << __FUNCTION__ << "\n";  }
    virtual ~Window() { }

    string name() const  { return m_name;  }
    virtual void display() const { cout << "Window::" << __FUNCTION__ << "\n"; }

    string m_name;
};

class WindowWithScrollbars : public Window
{
public:
    WindowWithScrollbars() { cout << __FUNCTION__ << "\n"; }
    virtual ~WindowWithScrollbars() {}

    virtual void display() const override { cout << "WindowWithScrollbars::" << __FUNCTION__ << "\n"; }

    int m_val;
};

// pass-by-value
void printNameAndDisplay( Window w )
{
    cout << w.name() << "\n";
    w.display();
}

// pass-by-reference
void printNameAndDisplayRef(const Window& w )
{
    cout << w.name() << "\n";
    w.display();
}



#endif // SLICINGOBJECT_H
