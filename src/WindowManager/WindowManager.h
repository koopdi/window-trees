/***********************************************************
 * Class Window Manager
 * *********************************************************
 * @file WindowManager.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 * @brief A collection of work spaces.
 */

#pragma once

#include <set>

#include "ServerInterface.h"
#include "Workspace.h"
#include "xtypes.h"

/***********************************************************
 * Class Window Manager
 * The window manager keeps track of the workspaces.
 **********************************************************/
class WindowManager
{
public:
	// public methods ----------------------------------------
	/**
	 * @brief Construct a new Window Manager object
	 * @param server
	 */
	WindowManager(ServerInterface* server);

	/**
	 * @brief do something with events?
	 * @param ev
	 */
	void update(XEvent& ev);

private:
	// private attributes ------------------------------------

	/// A collection of workspace pointers.
	std::set<Workspace*> workspaces;

	// private methods ---------------------------------------
};