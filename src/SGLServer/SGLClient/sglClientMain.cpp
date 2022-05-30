/***********************************************************
 * This is the main entry point to test WindowTrees using SGL
 * as a server backend and as a system layer that forwards
 * mouse and keeb inputs to the event system of said server.
 *
 * @file sglClientMain.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 * @brief An interactive graphics environment to test Windowing.
 */

#include <iostream>
#include "gwindow.h"
#include "gbutton.h"

using namespace std;
using namespace sgl;

const int WINDOW_WIDTH  = 640;
const int WINDOW_HEIGHT = 480;

void keyEv(GEvent ev, GWindow& win)
{
	if(ev.getKeyCode()==GEvent::ESCAPE_KEY)
	{
		win.close();
	}
}

// Add buttons to the window for sending events.
void addButtons(GWindow &win);

int main()
{
	// create a window
	GWindow* window = new GWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	// create a handy reference
	GWindow& win    = *window;

	// set window properties
	win.setExitOnClose(true);
	win.center();
	win.drawImage("edmonds.png");
	win.setWindowTitle("WindowTrees");
	win.setKeyListener([window](GEvent ev) { keyEv(ev, *window); });

	addButtons(win);


	// Don't delete the window, that memory is managed elsewhere.
	// delete window;
	return 0;
}

void addButtons(GWindow &win)
{
	win.addToolbar("toolbar"s);
	win.addToolbarItem("Distance"s);
	win.addToolbarItem("Speed");
	win.addToolbarItem("Acceleration");
	win.addToolbarItem("Jerk");
	// win.repaint();
	// GButton* distance = new GButton();
}