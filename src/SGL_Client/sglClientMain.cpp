#include <iostream>
using namespace std;

#include "gwindow.h"
using namespace sgl;

const int WINDOW_WIDTH  = 640;
const int WINDOW_HEIGHT = 480;

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

	cout << "test" << endl;
	delete window;
	cout << "test2" << endl;
	return 0;
}