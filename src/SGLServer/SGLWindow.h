#pragma once

/**
 * @file SGLServerWindow.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 * @brief A class to represent a window as a GRect object.
 * @note Not to be confused with GWindow, the underlying
 * object in SGLScreen.
 * @date 05-30-2022
 */

#include "gwindow.h"
#include "gobjects.h"
#include "types.h"

#include <memory>

struct SGLWindow {
	// This window's ID.
	const long ID;

	SGLWindow(sgl::GWindow& win);
	~SGLWindow();

private:
	sgl::GWindow& win;

	/// A counter to hold the
	static long nextID;

	/// The underlying graphics object.
	std::shared_ptr<sgl::GObject> sprite;
};

// class SGLServerWindow
// {
// public:
// 	SGLServerWindow(int height          = 0,
// 	                int width           = 0,
// 	                Point position      = Point{0, 0},
// 	                bool partVertically = true);
// 	int getHeight() const;
// 	int getWidth() const;
// 	int getPosition() const;
// 	int getID() const;
// 	void setHeight(int height);
// 	void setWidth(int width);
// 	void setPosition(Point position);

// private:
// 	static int idTicker;
// 	sgl::GObject* gobj;
// 	int height;
// 	int width;
// 	int windowID;
// 	Point position;
// };