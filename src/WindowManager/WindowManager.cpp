/**
 * @file WindowManager.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 * @brief
 */
#include <iostream>
#include <string>
using namespace std;

#include "WindowManager.h"

// public methods ------------------------------------------

/**
 * @brief Construct a new Window Manager
 * @param server
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
	for (long screenID : screens){
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
 * @param ev A tagged event union.
 */
void WindowManager::update(ev::Event& ev)
{
	try {
		cout << "Window Manager: event got" << endl;

		cout << "The real screenID: " << server->getScreens().at(0) << endl;

		switch (ev.type) {
		case ev::EventType::ADD:
			cout << "WindowManager: ev::ADD" << endl;
			cout << "ScreenID: " << ev.screenID << endl;

			if (workspaces.find(ev.screenID) != workspaces.end()) {
				// safe to access
				cout << "good" << endl;
				workspaces[ev.screenID]->addWindow(ev.add.winID);

			} else {
				cout << "not good" << endl;
			}
			break;

		case ev::EventType::REMOVE:
			workspaces[ev.screenID]->remWindow(ev.remove.winID);
			break;

		case ev::EventType::SWITCH_LAYOUT:
			workspaces[ev.screenID]->setLayoutMode(ev.layout.mode);
			break;

		case ev::EventType::ROTATE_SPLIT:
			workspaces[ev.screenID]->rotateSplit(ev.rotate.windowID);

		default:
			throw string("[ERROR] Window manager failed to handle WM level event");
		}

		if (workspaces.find(ev.screenID) != workspaces.end()) {
			std::cout << "rendering screen: " << ev.screenID << endl;
			workspaces[ev.screenID]->render();
		}else{
			cout << "Screen ID: " << ev.screenID << "not found in map" << endl;
		}
	} catch (string error) {
		cout << error << endl;
	}
}

void WindowManager::init()
{
	cout << "[WARNING] (WindowManager.cpp) => Init is not truly defined";
}