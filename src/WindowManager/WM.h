/***********************************************************
 * Class Workspace Manager
 * The workspace manager keeps track of the workspaces.
 * @file WM.h
 **********************************************************/

#include "ServerInterface.h"
#include "WMWorkspace.h"
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
	 * @brief Construct a new WM object
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