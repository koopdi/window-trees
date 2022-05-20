/***********************************************************
 * Class Window Manager
 * The window manager keeps track of the workspaces.
 * @file WindowManager.h
 **********************************************************/

#include "ServerInterface.h"
#include "Workspace.h"
#include "xtypes.h"

#include <set>

/**
 * @brief Manage Workspaces
 *
 */
class WM
{
public:
	// public methods ----------------------------------------
	/**
	 * @brief Construct a new Window Manager object
	 * @param server
	 */
	WM(ServerInterface* server);

	/**
	 * @brief do something with events?
	 * @param ev
	 */
	void update(XEvent& ev);

private:
	// private attributes ------------------------------------

	/// A collection of workspaces.
	std::set<WMWorkspace> workspaces;

	// private methods ---------------------------------------
};