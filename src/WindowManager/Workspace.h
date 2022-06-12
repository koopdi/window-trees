#pragma once
/**
 * @file Workspace.h
 * @author Christen Spadevechia
 * @date 6/10/2022
 * @brief Provides Workspace, a class that manages the creation and maintainance of multiple layouts
 * for a workspace.
 * Handles creating layouts, muxing (fanning out) events to each layout, and rendering the
 * selected layout.
*/


#include "types.h"
#include "ServerInterface.h"
#include "WindowTreeInterface.h"

#include "LemonFir.h"
#include "MasterStack.h"
#include "HeapTree.h"

#include <memory>

class WindowTree;

/** @brief creates and maanges layouts for a workspace */
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

	/// Switch the positions of A and B in the active layout.
	void swapWindows(long windowA, long windowB);

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

	/**
	 * @brief Check if a layout is available on this workspace
	 * and get a pointer to it.
	 * @param mode The name of the layout.
	 * @return WindowTreeInterface* a pointer to the layout or
	 * nullptr if the layout is not found.
	 */
	WindowTreeInterface* getTree(ev::TreeMode mode);
};

bool operator<(std::shared_ptr<Workspace>& a, std::shared_ptr<Workspace>& b);