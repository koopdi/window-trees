
#ifndef XSCREEN_H
#define XSCREEN_H
#include <X11/Xlib.h>
#include "unordered_set"

class XScreen{
	std::unordered_set<Window> windows;

	XScreen();
};

#endif
