/**
 * @file WindowManager.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-23
 *
 * @copyright Copyright (c) 2022
 *
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

	/// A collection of workspaces.
	std::set<Workspace> workspaces;

	// private methods ---------------------------------------
};