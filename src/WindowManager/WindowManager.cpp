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
	if (server == nullptr)
	{
		throw "Failed to initialize Workspace Manager: "
		      "Provided server is null.";
	}

	// add a workspace
	shared_ptr<Workspace> spw = make_shared<Workspace>();
	workspaces.insert(spw);
}

/**
 * @brief This function is called whenever the server sends
 *  an event.
 * @param ev An event union.
 */
void WindowManager::update(ev::Event& ev)
{
	cout << "Window Manager: event got" << endl;
	if (ev.type == ev::EventType::ADD)
	{
		(*workspaces.begin()).get()->addWindow(true, ev.add.atributeA, 50.0);
	}
}