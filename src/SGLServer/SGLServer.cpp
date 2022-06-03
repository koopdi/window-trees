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

	#if _WIN32
	win.drawImage("../../../res/edmonds.png");
	#else
	win.drawImage("res/edmonds.png");
	#endif

	win.setWindowTitle("WindowTrees");

	win.setKeyListener([this](GEvent ev) { keyEv(ev); });

	// Add some buttons.
	addButtons();

	win.setMenuListener([this](GEvent ev) { menuEv(ev); });

}

bool SGLServer::contains(long windowID)
{
	if(winDex.find(windowID) != winDex.end()){
		return true;
	} else {
		// throw string("Window not found.");
		cout << "Window ID does not exist." << endl;
		return false;
	}
}

void SGLServer::setArea(long windowID, Area a)
{
	if(contains(windowID)){
		sglWin gWin = winDex[windowID];
		gWin.get()->setArea(a);
	} else {
		cout << "Failed to set area." << endl;
	}
}

Area SGLServer::getArea(long windowID)
{
	Area foo;
	if(contains(windowID)){
	sglWin gWin = winDex[windowID];
	foo = gWin.get()->getArea();
	} else {
		cout << "Failed to get area -- Returning bogus data." << endl;
		foo = {-1, -1, -1, -1};
	}
	return foo;
}
Area SGLServer::getScreenSize(long screenID)
{
	Area foo;
	foo.width = window->getCanvasWidth();
	foo.height = window->getCanvasHeight();

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
			evAdd->add.winID = (*gwin).ID;
			winDex[(*gwin).ID] = gwin;

			evFun(evAdd);
		} else if (action == "toolbar/Remove") {
			cout << "remove was pressed, creating event..." << endl;

			if (!winDex.empty()) {
				// get the first window
				sglWin gwin = (*winDex.begin()).second;
				// remove the window
				winDex.erase(winDex.begin());

				// create remove event
				ev::Event* evRem    = new ev::Event;
				evRem->type         = ev::EventType::REMOVE;
				evRem->remove.winID = (*gwin).ID;
				// send remove event to event handler
				evFun(evRem);
				// free event memory
				delete evRem;
				// The window will be automatically removed and freed.
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