#include "SGLServer.h"
#include "gchooser.h"
#include "gobjects.h"
#include "Logger.h"
#include <string>
using namespace std;

// Global logger object
extern Logger glogger;


SGLServer::SGLServer()
{
	glogger.verb("LOGGY IS IN SGL SERVER!");

	using sgl::GEvent;
	using sgl::GWindow;

	// create a window
	window       = new GWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	// create a handy reference
	GWindow& win = *window;

	// set window properties
	win.setWindowTitle("WindowTrees");
	win.setExitOnClose(true);
	win.setAutoRepaint(false);
	win.center();

	// #if _WIN32
	// 	win.drawImage("../../../res/edmonds.png");
	// #else
	// 	win.drawImage("res/edmonds.png");
	// #endif

	// Add some buttons.
	addButtons();

	// Register event callbacks.
	win.setKeyListener([this](GEvent ev) { keyEv(ev); });
	win.setClickListener([this](GEvent ev) { clickEv(ev); });
	win.setMenuListener([this](GEvent ev) { menuEv(ev); });
	win.setWindowListener([this](GEvent ev) { screenEv(ev); });
}

bool SGLServer::contains(long windowID)
{
	if (winDex.find(windowID) != winDex.end()) {
		return true;
	} else {
		cout << "SGLServer, contains:" << endl;
		cout << "Window ID " << windowID << " does not exist." << endl;
		// throw string("Window ID does not exist.");
		return false;
	}
}

void SGLServer::setArea(long windowID, Area a)
{
	if (contains(windowID)) {
		winPtr gWin = winDex[windowID];
		gWin.get()->setArea(a);
		window->repaint();
	} else {
		cout << "Failed to set area." << endl;
	}
}

Area SGLServer::getArea(long windowID)
{
	Area foo;
	if (contains(windowID)) {
		winPtr gWin = winDex[windowID];
		foo         = gWin.get()->getArea();
	} else {
		cout << "Failed to get area -- Returning bogus data." << endl;
		foo = {-1, -1, -1, -1};
	}
	return foo;
}
Area SGLServer::getScreenSize(long screenID)
{
	Area foo;
	foo.x      = 0;
	foo.y      = 0;
	foo.width  = window->getCanvasWidth();
	foo.height = window->getCanvasHeight();

	return foo;
}

std::vector<long> SGLServer::getScreens()
{
	std::vector<long> foo{99};
	return foo;
}

std::vector<long> SGLServer::getWindows(long screenID)
{
	std::vector<long> foo;
	for (auto [ID, win] : winDex) {
		foo.push_back(ID);
	}
	return foo;
}

void SGLServer::setInitCallback(InitHandlerFn fn) { inFun = fn; }

void SGLServer::setEventCallback(EventHandlerFn fn) { evFun = fn; }

void SGLServer::run()
{
	string block;
	while (cin >> block) { // loop forever until sgl quits
		cout << block;
	}
}

winPtr SGLServer::getWin(sgl::GObject* obj)
{
	for (auto [selectID, winP] : winDex) {
		if (winP.get()->sprite.get() == obj) {
			return winP;
		}
	}
	return nullptr;
}

bool SGLServer::dropDownSelect(long windowID)
{
	// cout << "selecting ID# " << windowID << endl;
	int count = dropDown->getItemCount();
	for (int idx = 0; idx < count; idx++) {
		if (stol(dropDown->getItem(idx)) == windowID) {
			dropDown->setSelectedIndex(idx);
			return true;
		}
	}
	return false;
}

void SGLServer::evRotate(long windowID)
{
	// create rotate event
	ev::Event* evRot    = new ev::Event;
	evRot->type         = ev::EventType::ROTATE_SPLIT;
	evRot->rotate.winID = windowID;
	evRot->screenID     = 99;
	// send rotate event to event handler
	evFun(evRot);
	// free event memory
	delete evRot;
}

void SGLServer::clickEv(sgl::GEvent e)
{
	sgl::EventType eType = e.getType();
	if (eType == sgl::EventType::MOUSE_CLICKED) {
		int x = e.getX();
		int y = e.getY();
		// find the gobject that was clicked
		if (sgl::GObject* g = window->getGObjectAt(x, y)) {
			// Find g in the winDex.
			if (winPtr winP = getWin(g)) {
				if (e.isLeftClick()) { // select g
					// send focus event
					ev::Event* evFocus   = new ev::Event;
					evFocus->type        = ev::EventType::FOCUS;
					evFocus->screenID    = 99;
					evFocus->focus.winID = winP->ID;
					evFun(evFocus);
					delete evFocus;

					// Highlight g.
					g->setLineWidth(5);
					g->setColor("yellow");
					window->repaint();

					// Reset the outline.
					g->setLineWidth(1);
					g->setColor("black");

					// select g in the drop down chooser
					dropDownSelect(winP->ID);

				} else if (e.isMiddleClick()) { // remove g
					remove(winP->ID);

				} else { // rotate g
					evRotate(winP->ID);
				}

			} // g is not a window
		}   // nothing was clicked
	}     // not a click event
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

		if (action == "toolbar/Add") { // ADD
			// Create a new window.
			winPtr gwin        = make_shared<serverWindow>(*window);
			// add to index
			winDex[(*gwin).ID] = gwin;
			// add to dropdown
			dropDown->addItem(to_string((*gwin).ID));

			// create event
			ev::Event* evAdd = new ev::Event;
			evAdd->type      = ev::EventType::ADD;
			evAdd->add.winID = (*gwin).ID;
			evAdd->screenID  = 99;
			// send event
			evFun(evAdd);
			// free
			delete evAdd;

		} else if (action == "toolbar/Remove") { // REMOVE
			// check which window is selected in the dropdown
			if (!dropDown->isEmpty()) {
				remove(stol(dropDown->getSelectedItem()));
			}

		} else if (action == "toolbar/Switch Layout") { // SWITCH_LAYOUT
			ev::Event* evSwitch   = new ev::Event;
			evSwitch->type        = ev::EventType::SWITCH_LAYOUT;
			evSwitch->screenID    = 99;
			evSwitch->layout.mode = ev::TreeMode::NEXT;
			evFun(evSwitch);
			delete evSwitch;

		} else if (action == "toolbar/Swap Windows") { // SWAP_WINDOWS
			ev::Event* evSwap = new ev::Event;
			evSwap->type      = ev::EventType::SWAP_WINDOWS;
			evSwap->screenID  = 99;

			if (dropDown->getItemCount() > 1) {
				evSwap->swap.winA = stol(dropDown->getItem(0));
				evSwap->swap.winB = stol(dropDown->getSelectedItem());
				// cout << "sending swap event" << endl;
				evFun(evSwap);
				delete evSwap;
			} else {
				// cout << "NOT sending swap event" << endl;
			}
		}
	}
}

void SGLServer::screenEv(sgl::GEvent ev)
{
	sgl::EventType type = ev.getType();
	if (type == sgl::EventType::WINDOW_RESIZED) { // RESIZE
		ev::Event* evResize   = new ev::Event;
		evResize->type        = ev::EventType::RESIZE;
		evResize->screenID    = 99;

		evResize->resize.size = getScreenSize(99);
		evFun(evResize);

		delete evResize;
	}
}

void SGLServer::remove(long windowID)
{
	if (contains(windowID)) {
		// get the specified window
		winPtr gwin = winDex[windowID];
		// remove the specified window
		winDex.erase(windowID);

		// send remove event
		evRemove((*gwin).ID);

		// refresh the dropdown chooser
		dropDown->clearItems();
		for (auto& [ID, winD] : winDex) {
			dropDown->addItem(to_string(ID));
		}
	} // else invalid ID
}

void SGLServer::evRemove(long windowID)
{
	// create remove event
	ev::Event* evRem    = new ev::Event;
	evRem->type         = ev::EventType::REMOVE;
	evRem->remove.winID = windowID;
	evRem->screenID     = 99;
	// send remove event to event handler
	evFun(evRem);
	// free event memory
	delete evRem;
}

void SGLServer::addButtons()
{
	sgl::GWindow& win = *window;

	dropDown          = new sgl::GChooser();
	win.addToRegion(dropDown, "North");

	// Add a toolbar.
	win.addToolbar("toolbar");
	// Add buttons.
	win.addToolbarItem("Add");
	win.addToolbarItem("Remove");
	win.addToolbarItem("Switch Layout");
	win.addToolbarItem("Swap Windows");

	// Add a divider between the novelty placeholders.
	win.addToolbarSeparator();
	// win.addToolbarItem("Distance");
	// win.addToolbarItem("Speed");
	// win.addToolbarItem("Acceleration");
	// win.addToolbarItem("Jerk");
	// win.addToolbarItem("Snap");
	// win.addToolbarItem("Crackle");
	// win.addToolbarItem("Pop");
}