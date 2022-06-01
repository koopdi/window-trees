#include "SGLServer.h"
#include <string>
using namespace std;

SGLServer::SGLServer()
{
	ID_TICKER = 0;

	using sgl::GWindow;
	using sgl::GEvent;

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

void SGLServer::setArea(long windowID, Area area)
{
	sgl::GWindow& win = *window;

	// win.add();
}

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
	if (ev.getClass() == sgl::EventClass::ACTION_EVENT)
	{
		string action = ev.getActionCommand();
		cout << action << endl;

		if(action == "toolbar/Add")
		{
			cout << "add was pressed, creating event..." << endl;
			ev::Event* ev = new ev::Event;
			ev->type = ev::EventType::ADD;
			ev->add.atributeA = ++ID_TICKER;

			idPair newWindow;
			// newWindow.first = make_shared<sgl::GObject>;
			// newWindow.second = ev->add.atributeA;

			evFun(ev);
		}
		else if (action == "toolbar/Remove")
		{
			cout << "remove was pressed, creating event..." << endl;
			ev::Event* ev = new ev::Event;
			ev->type = ev::EventType::REMOVE;
			ev->remove.atributeB = 13;

			evFun(ev);
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