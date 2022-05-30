#pragma once

/**
 * @file SGLServerWindow.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 * @brief A class to store the underlying GObject.
 * @date 05-30-2022
 */

#include "types.h"
 #include "gobjects.h"

class SGLServerWindow
{
public:
	SGLServerWindow(int height          = 0,
	                int width           = 0,
	                Point position      = Point{0, 0},
	                bool partVertically = true);
	int getHeight() const;
	int getWidth() const;
	int getPosition() const;
	int getID() const;
	void setHeight(int height);
	void setWidth(int width);
	void setPosition(Point position);

private:
	static int idTicker;
	sgl::GObject* gobj;
	int height;
	int width;
	int windowID;
	Point position;
};