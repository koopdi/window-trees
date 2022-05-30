/***********************************************************
 * Class Window Manager
 * *********************************************************
 * @file WindowManager.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 * @brief A collection of work spaces.
 */

#pragma once

#include <memory>
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

	WindowManager(ServerInterface* server);

	void update(ev::Event& ev);

private:
	// private attributes ------------------------------------

	/// A collection of window IDs.
	std::set<int> winDex;

	/// A collection of workspace pointers.
	std::set<std::shared_ptr<Workspace>> workspaces;

	/// A pointer to the server.
	ServerInterface* server;

	// private methods ---------------------------------------
};