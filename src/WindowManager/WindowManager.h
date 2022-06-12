#pragma once

/***********************************************************
 * Class Window Manager
 * *********************************************************
 * @file WindowManager.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 * @date 6/10/2022
 * @brief A collection of work spaces.
 * Handles window events by calling functions on the correct workspace.
 * (Theoretically) provides a means of supporting multihead in the future by muxing (fanning out)
 * events to their respective workspaces.
 */


#include <memory>
#include <map>

#include "ServerInterface.h"
#include "Workspace.h"
// #include "xtypes.h"
#include "Events.h"

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

	void init();

private:
	// private attributes ------------------------------------

	/// A collection of workspace pointers.
	std::unordered_map<long, std::shared_ptr<Workspace>> workspaces;

	/// A pointer to the server.
	ServerInterface* server;

	// private methods ---------------------------------------
};