#include "SGLWindow.h"
#include <iomanip>
#include <sstream>

using namespace std;
using namespace sgl;

long SGLWindow::nextID = 0;

SGLWindow::SGLWindow(GWindow& win) : ID(nextID++), win(win)
{
	int width  = win.getCanvasWidth();
	int height = win.getCanvasHeight();

	int x      = 13 * ID % (width - 100);
	int y      = 23 * ID % (height - 200);

	int r      = 5 * ID % 0xFF;
	int g      = 7 * ID % 0xFF;
	int b      = 13 * ID % 0xFF;

	std::stringstream fillColor;

	fillColor << '#';
	fillColor << setfill('0') << setw(2) << hex << r;
	fillColor << setfill('0') << setw(2) << hex << g;
	fillColor << setfill('0') << setw(2) << hex << b;

	cout << endl << fillColor.str() << endl;

	sprite = make_shared<GRect>(x, y, 100, 200);
	win.add(*sprite);
	(*sprite).sendToFront();
	(*sprite).setColor("#000000");
	(*sprite).setFillColor(fillColor.str());
	(*sprite).setOpacity(.5);
	// win.repaint();
}

SGLWindow::~SGLWindow()
{
	// remove this gobject from the gwindow
	win.remove(*sprite);
	// the memory will be freed automatically
}