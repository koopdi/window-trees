#pragma once
/**
 * @file Workspace.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney (you@domain.com)
 */


#include "types.h"
#include "ServerInterface.h"
#include "WindowTreeInterface.h"

#include "LemonFir.h"
#include "MasterStack.h"
#include "HeapTree.h"

#include <memory>

class WindowTree;


class Workspace
{
public:
	// public methods ----------------------------------------

	/**
	 * @brief Construct a new Workspace object
	 */
	Workspace(ServerInterface* server, long screenID);

	void render();

	void addWindow(long windowID);

	void remWindow(long windowID);

	void rotateSplit(long windowID);

	void resize(Area area);

	void setLayoutMode(ev::TreeMode mode);

	std::vector<ev::TreeMode> getAvailableModes();

	ev::TreeMode getActiveMode();
private:
	// private attributes ------------------------------------

	/// window tree ptrs
	std::unordered_map<ev::TreeMode, WindowTreeInterface*> windowTrees;

	/// the size of the workspace
	Area area;

	/// the ServerInterface that the workspace will render to
	ServerInterface* server;

	/// the layout that is currently active
	ev::TreeMode treeLayoutMode;

	// private methods ---------------------------------------
};

bool operator<(std::shared_ptr<Workspace>& a, std::shared_ptr<Workspace>& b);