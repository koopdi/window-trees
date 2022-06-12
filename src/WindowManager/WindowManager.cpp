/**
 * @file WindowManager.cpp
 * @author Christen Spadevechia, Travis McKinney
 * @brief provide an implementation for the functions defined in WindowManager.h
 * @date 6/10/2022
 */
#include <iostream>
#include <string>
using namespace std;

#include "WindowManager.h"

// public methods ------------------------------------------

/**
 * @brief Construct a new Window Manager
 * @param server a pointer to the ServerInterface backend for the windowing system being managed
 */
WindowManager::WindowManager(ServerInterface* server) : server(server)
{
	if (server == nullptr) {
		throw "Failed to initialize Workspace Manager: "
		      "Provided server is null.";
	}

	cout << "Getting screens" << endl;
	// create a workspace for each screen
	vector<long> screens = server->getScreens();
	for (long screenID : screens) {
		cout << screenID << endl;
	}
	for (long screenID : screens) {
		cout << "	// create a workspace for each screen" << endl;
		cout << "screenID: " << screenID << endl;
		shared_ptr<Workspace> spw = make_shared<Workspace>(server, screenID);
		workspaces[screenID]      = spw;
	}
}

/**
 * @brief This function is called whenever the server sends
 *  an event.
 * @param ev A tagged event union to be handled.
 */
void WindowManager::update(ev::Event& ev)
{
	try {
		// cout << "Window Manager: event got" << endl;
		// cout << "The real screenID: " << server->getScreens().at(0) << endl;

		switch (ev.type) {
		case ev::EventType::ADD:
			// cout << "WindowManager: ev::ADD" << endl;
			// cout << "ScreenID: " << ev.screenID << endl;

			if (workspaces.find(ev.screenID) != workspaces.end()) {
				// safe to access
				// cout << "good" << endl;
				workspaces[ev.screenID]->addWindow(ev.add.winID);

			} else {
				// cout << "not good" << endl;
			}
			break;

		case ev::EventType::REMOVE:
			workspaces[ev.screenID]->remWindow(ev.remove.winID);
			break;

		case ev::EventType::FOCUS:
			// cout << "Window focused, ID: " << ev.focus.winID << endl;
			break;

		case ev::EventType::SWAP_WINDOWS:
			workspaces[ev.screenID]->swapWindows(ev.swap.winA, ev.swap.winB);
			break;

		case ev::EventType::MOVE_WINDOW:
			break;

		case ev::EventType::SWITCH_LAYOUT:
			workspaces[ev.screenID]->setLayoutMode(ev.layout.mode);
			break;

		case ev::EventType::ROTATE_SPLIT:
			// cout << "Window manager Rotate" << endl;
			workspaces[ev.screenID]->rotateSplit(ev.rotate.winID);
			break;

		case ev::EventType::RESIZE:
			workspaces[ev.screenID]->resize(ev.resize.size);
			break;

		default:
			throw string("[ERROR] Window manager failed to handle WM level event");
		}

		if (workspaces.find(ev.screenID) != workspaces.end()) {
			// std::cout << "rendering screen: " << ev.screenID << endl;
			workspaces[ev.screenID]->render();
		} else {
			cout << "Screen ID: " << ev.screenID << "not found in map" << endl;
		}
	} catch (string error) {
		cout << error << endl;
	}
}
/** @brief called when the WindowManager is created, does necessary init work (none for now)*/
void WindowManager::init()
{
	cout << "[WARNING] (WindowManager.cpp) => Init is not truly defined";
}