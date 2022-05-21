#pragma once

#include "types.h"

class DisplayServerWindow {
public:
    DisplayServerWindow(int height = 0, int width = 0,
    Point position = Point{0, 0}, bool partVertically = true);
    int getHeight() const;
    int getWidth() const;
    int getPosition() const;
    int getID() const;
    void setHeight(int height);
    void setWidth(int width);
    void setPosition(Point position);

private:
    static int idTicker;
    //sgl::GObject* gobj;
    int height;
    int width;
    int windowID;
    Point position;
};