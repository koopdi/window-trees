#include "SGLWindow.h"

using namespace std;
using namespace sgl;

long SGLWindow::nextID = 0;

SGLWindow::SGLWindow(GWindow& win) : ID(nextID++), win(win)
{
	sprite = make_shared<GRect>(10, 10, 100, 200);
	win.add(*sprite);
	(*sprite).sendToFront();
	(*sprite).setColor("#ff00ff");
	win.repaint();
}

SGLWindow::~SGLWindow()
{
	//  win.remove(*sprite);
	GObject* obj = sprite.get();
	win.remove(obj);
	// win.remove(sprite.get());
}