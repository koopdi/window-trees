#include "SGLServer.h"
#include "gchooser.h"
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
}

bool SGLServer::contains(long windowID)
{
	if (winDex.find(windowID) != winDex.end()) {
		return true;
	} else {
		cout << "Window ID does not exist." << endl;
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
	std::vector<long> foo {99};
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
	string block;
	while (cin >> block) { // loop forever until sgl quits
		cout << block;
	}

	// render looooop?
	// window->repaint();
	// std::sleep(200);
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
	// create remove event
	ev::Event* evRot    = new ev::Event;
	evRot->type         = ev::EventType::ROTATE_SPLIT;
	evRot->rotate.windowID = windowID;
	evRot->screenID = 99;
	// send remove event to event handler
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

		if (sgl::GObject* g = window->getGObjectAt(x, y)) {
			// Find g in the winDex.
			if (winPtr winP = getWin(g)) {
				if (e.isLeftClick()) { // select g
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
					// cout << "rotate g" << endl;
					evRotate(winP->ID);
				}
			} // g is not a window
		}   // nothing was clicked
	}     // not a click event
}

// this function triggers when it shouldn't
void SGLServer::dropDownEv(sgl::GEvent ev)
{
	// if(ev.getClass() == sgl::EventClass::)
	// cout << "drop down" << ev.getActionCommand() << " clicked" << endl;
	// remove(stol(ev.getActionCommand()));
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
		// cout << action << endl;

		if (action == "toolbar/Add") {
			// cout << "add was pressed, creating event..." << endl;
			ev::Event* evAdd   = new ev::Event;
			evAdd->type        = ev::EventType::ADD;

			winPtr gwin        = make_shared<serverWindow>(*window);
			evAdd->add.winID   = (*gwin).ID;
			winDex[(*gwin).ID] = gwin;

			evAdd->screenID = 99;

			dropDown->addItem(to_string((*gwin).ID));

			evFun(evAdd);
		} else if (action == "toolbar/Remove") {
			// cout << "remove was pressed, creating event..." << endl;
			if (dropDown->isEmpty()) {
				remove(-1);
			} else {
				remove(stol(dropDown->getSelectedItem()));
			}
		}
	}
}

void SGLServer::remove(long windowID)
{
	if (!winDex.empty()) {
		winPtr gwin;
		if (windowID == -1) {
			// get the first window
			gwin = (*winDex.begin()).second;
			// remove the first window
			evRemove((*gwin).ID);
			winDex.erase(winDex.begin());
			// window->repaint();
		} else if (contains(windowID)) {
			// get the specified window
			gwin = winDex[windowID];
			// remove the specified window
			winDex.erase(windowID);
			evRemove((*gwin).ID);
		} // else invalid ID
	}   // else no windows at all

	// refresh the dropdown chooser
	dropDown->clearItems();
	for (auto& [ID, winD] : winDex) {
		dropDown->addItem(to_string(ID));
	}
}

void SGLServer::evRemove(long windowID)
{
	// create remove event
	ev::Event* evRem    = new ev::Event;
	evRem->type         = ev::EventType::REMOVE;
	evRem->remove.winID = windowID;
	evRem->screenID = 99;
	// send remove event to event handler
	evFun(evRem);
	// free event memory
	delete evRem;
	// The window will be automatically removed and freed.
}

void SGLServer::addButtons()
{
	if (window == nullptr) {
		throw "cannot add buttons"s;
	}
	sgl::GWindow& win = *window;

	dropDown          = new sgl::GChooser();
	win.addToRegion(dropDown, "North");

	// dropDown->setActionListener([this](sgl::GEvent ev) { dropDownEv(ev); });
	dropDown->setDoubleClickListener([this](sgl::GEvent ev) { dropDownEv(ev); });
	// win.setMenuListener([this](GEvent ev) { menuEv(ev); });

	// Add a toolbar.
	win.addToolbar("toolbar");
	// Add buttons.
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