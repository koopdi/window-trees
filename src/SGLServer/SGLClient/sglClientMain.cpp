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

#include "SGLServer.h"

#include "WindowManager.h"

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

	// Create a SGL Server for the Window Manager to interface with.
	// This is broken, undefined reference to vtable for SGLServer.
	// It could be a build configuration thing but I think it's todo
	// with the implementation of ServerInterface in SGLServer.
	// SGLServer* server = new SGLServer();


	// Don't delete the window, that memory is managed elsewhere.
	// delete window;
	return 0;
}

void addButtons(GWindow &win)
{
	win.addToolbar("toolbar");
	win.addToolbarItem("Add");
	win.addToolbarItem("Remove");
	win.addToolbarSeparator();
	win.addToolbarItem("Distance");
	win.addToolbarItem("Speed");
	win.addToolbarItem("Acceleration");
	win.addToolbarItem("Jerk");
	win.addToolbarItem("Snap");
	win.addToolbarItem("Crackle");
	win.addToolbarItem("Pop");
}