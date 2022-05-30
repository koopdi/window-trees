#include "SGLServer.h"
#include <string>
using namespace std;

SGLServer::SGLServer()
{
	using sgl::GWindow;
	using sgl::GEvent;

	// create a window
	window       = new GWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	// create a handy reference
	GWindow& win = *window;

	// set window properties
	win.setExitOnClose(true);
	win.center();
	win.drawImage("edmonds.png");
	win.setWindowTitle("WindowTrees");

	win.setKeyListener([this](GEvent ev) { keyEv(ev); });

	// Add some buttons.
	addButtons();

	win.setMenuListener([this](GEvent ev) { menuEv(ev); });
}

void SGLServer::setArea(long windowID, Area area) {}

Area SGLServer::getArea(long windowID)
{
	Area foo;
	return foo;
}
Area SGLServer::getScreenSize(long screenID)
{
	Area foo;
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
	// forward events to window manager?
	// event forwarding can happen asynchronously.
}

void SGLServer::keyEv(sgl::GEvent ev)
{
	sgl::GWindow& win = *window;

	if (ev.getKeyCode() == sgl::GEvent::KeyCode::ESCAPE_KEY)
	{
		win.close();
	}
}

void SGLServer::menuEv(sgl::GEvent ev)
{
	// GWindow& win = *window;
	if (ev.getClass() == sgl::EventClass::ACTION_EVENT)
	{
		string action = ev.getActionCommand();
		cout << action << endl;

		if(action == "add")
		{
			ev::Event* ev = new ev::Event;
			ev->type = ev::EventType::ADD;
			ev->add.atributeA = 13;
		}
	}
}

void SGLServer::addButtons()
{
	if (window == nullptr)
	{
		throw "cannot add buttons"s;
	}
	sgl::GWindow& win = *window;

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