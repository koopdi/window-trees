#pragma once

/**
 * @file WindowScreen.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 * @brief A class to represent a monitor as a GWindow object.
 */

#include <map>

#include "SGLWindow.h"

class SGLScreen
{
	// std::map<int, SGLServerWindow> windows;

	SGLScreen();
	void addWindow(int windowID);
	void remWindow(int windowID);
};