#include <iostream>
using namespace std;

#include "gwindow.h"
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

	// this doesn't close the window
	// delete window; // don't delete the window
	return 0;
}