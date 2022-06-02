#include "SGLServer.h"
#include "ginteractor.h"
#include "gobjects.h"
#include <string>
using namespace std;

SGLServer::SGLServer()
{
	using sgl::GEvent;
	using sgl::GWindow;

	// create a window
	window       = new GWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	// create a handy reference
	GWindow& win = *window;

	// set window properties
	win.setExitOnClose(true);
	win.center();

	// #if _WIN32
	// win.drawImage("../../../res/edmonds.png");
	// #else
	// win.drawImage("res/edmonds.png");
	// #endif

	win.setWindowTitle("WindowTrees");

	win.setKeyListener([this](GEvent ev) { keyEv(ev); });

	// Add some buttons.
	addButtons();

	win.setMenuListener([this](GEvent ev) { menuEv(ev); });

	sgl::GRect* rect = new sgl::GRect(0, 0, 100, 200);
	win.add(rect);
}

void SGLServer::setArea(long windowID, Area area)
{
	sgl::GWindow& win = *window;

	// win.add();
}

Area SGLServer::getArea(long windowID)
{
	Area foo;
	foo.x = 0;
	return foo;
}
Area SGLServer::getScreenSize(long screenID)
{
	Area foo;
	foo.x = 0;

	return foo;
}

std::vector<long> SGLServer::getScreens()
{
	std::vector<long> foo;
	return foo;
}

std::vector<long> SGLServer::getWindows(long screenID)
{
	std::vector<long> foo;
	return foo;
}

void SGLServer::setInitCallback(InitHandlerFn fn) { inFun = fn; }

void SGLServer::setEventCallback(EventHandlerFn fn) { evFun = fn; }

void SGLServer::run()
{
	// render looooop?
	// window->repaint();
	// std::sleep(200);
}

void SGLServer::keyEv(sgl::GEvent ev)
{
	sgl::GWindow& win = *window;

	if (ev.getKeyCode() == sgl::GEvent::KeyCode::ESCAPE_KEY) {
		win.close();
	}
}

void SGLServer::menuEv(sgl::GEvent e)
{
	if (e.getClass() == sgl::EventClass::ACTION_EVENT) {
		string action = e.getActionCommand();
		cout << action << endl;

		if (action == "toolbar/Add") {
			cout << "add was pressed, creating event..." << endl;
			ev::Event* evAdd = new ev::Event;
			evAdd->type      = ev::EventType::ADD;

			sglWin gwin      = make_shared<SGLWindow>(*window);

			winDex.insert(gwin);

			evFun(evAdd);
		} else if (action == "toolbar/Remove") {
			cout << "remove was pressed, creating event..." << endl;

			if (!winDex.empty()) {
				sglWin gwin = *winDex.begin();
				winDex.erase(winDex.begin());
				ev::Event* evRem    = new ev::Event;
				evRem->type         = ev::EventType::REMOVE;
				evRem->remove.winID = (*gwin).ID;

				evFun(evRem);
			}
		}
	}
}

void SGLServer::addButtons()
{
	if (window == nullptr) {
		throw "cannot add buttons"s;
	}
	sgl::GWindow& win = *window;
	// sgl::GInteractor* = new sgl::GInteractor::
	// win.addToRegion()
	win.addToolbar("toolbar");
	win.addToolbarItem("Add");
	win.addToolbarItem("Remove");
	// Add a divider between the novelty placeholders.
	win.addToolbarSeparator();
	win.addToolbarItem("Distance");
	win.addToolbarItem("Speed");
	win.addToolbarItem("Acceleration");
	win.addToolbarItem("Jerk");
	win.addToolbarItem("Snap");
	win.addToolbarItem("Crackle");
	win.addToolbarItem("Pop");
}