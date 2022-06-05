#include "SGLWindow.h"
#include <iomanip>
#include <sstream>

using namespace std;
using namespace sgl;

long serverWindow::nextID = 0;

serverWindow::serverWindow(GWindow& win) : ID(nextID++), win(win)
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

	// cout << endl << fillColor.str() << endl;

	sprite = make_shared<GRect>(x, y, 100, 200);
	win.add(*sprite);
	(*sprite).sendToFront();
	(*sprite).setColor("#000000");
	(*sprite).setFillColor(fillColor.str());
	(*sprite).setOpacity(.5);
	// win.repaint();
}

serverWindow::~serverWindow()
{
	// remove this gobject from the gwindow
	win.remove(*sprite);
	// the memory will be freed automatically
}

Area serverWindow::getArea()
{
	Area foo;
	foo.width = sprite.get()->getWidth();
	foo.height = sprite.get()->getHeight();
	foo.x = sprite.get()->getX();
	foo.y = sprite.get()->getY();
	return foo;
}

void serverWindow::setArea(Area a)
{
	sprite.get()->setLocation(a.x, a.y);
	sprite.get()->setSize(a.width, a.height);
}