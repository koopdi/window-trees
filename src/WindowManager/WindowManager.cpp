/**
 * @file WindowManager.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 * @brief
 */

#include <string>

#include "WindowManager.h"

using namespace std;

// public methods ------------------------------------------

/**
 * @brief Construct a new Window Manager
 * @param server
 */
WindowManager::WindowManager(ServerInterface* server)
{
	if (server == nullptr)
	{
		throw "Failed to initialize Workspace Manager: "
		      "Provided server is null.";
	}
}

/**
 * @brief This function is called whenever the server sends
 *  an event.
 * @param ev An event union.
 */
void WindowManager::update(XEvent& ev)
{

}