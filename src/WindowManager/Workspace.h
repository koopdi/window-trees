/**
 * @file Workspace.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney (you@domain.com)
 */

#pragma once

#include "WindowNode.h"
#include "WindowTree.h"
#include "types.h"
#include "ServerInterface.h"
#include "WindowTreeInterface.h"

#include <memory>

class WindowTree;


class Workspace
{
public:
	// public methods ----------------------------------------

	/**
	 * @brief Construct a new Workspace object
	 */
	Workspace(ServerInterface* server, WindowTreeInterface* mtree = nullptr);

	void setHeight(int height);

	void setWidth(int width);

	void setPosition(Point position);

	bool addWindow(int windowID, double part1Size);

	bool removeWindow(int windowID);

	/// operator to allow using sorted containers
	bool operator<(Workspace& other);

	int getHeight() const;

	int getWidth() const;

	Point getPosition() const;

	int getNumWindows() const;

	void render();
private:
	// private attributes ------------------------------------

	/// a pointer to the window tree
	WindowTree* tree;
	WindowTreeInterface* metaTree;

	/// the height of the workspace
	int height;

	/// the width of the workspace
	int width;

	int workspaceID;

	/// the number of windows in the workspace
	int numWindows;

	/// a point representing the position of the top left corner of the workspace
	Point position;

	ServerInterface* server;

	// private methods ---------------------------------------
	void renderTree(WindowNode* node, Area bounds);
};

bool operator<(std::shared_ptr<Workspace>& a, std::shared_ptr<Workspace>& b);