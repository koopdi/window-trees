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

	// add a workspace
	shared_ptr<Workspace> spw = make_shared<Workspace>(server);
	workspaces.insert(spw);
}


void WindowManager::renderAll(){
	for (auto& workspace : workspaces){
		workspace->render();
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
		if (ev.type == ev::EventType::ADD) {
			(workspaces.begin())->get()->addWindow(ev.add.winID, 0.5);
		} else if (ev.type == ev::EventType::REMOVE) {
			(workspaces.begin())->get()->removeWindow(13);
		}

		renderAll();

	} catch (string error) {
		cout << error << endl;
	}
}