#pragma once

/** @file
 * Describes the MasterStack class, a class that extends the WindowTreeInterface and that
 * implements a master:stack layout where there is one large window that takes up half of
 * a workspace, and n other windows that equally subdivide the reminaing space.
 * @author Christen Spadavecchia
 * @date Spring 2022
 * CS 133
*/

#include "ServerInterface.h"
#include "WindowTreeInterface.h"
#include "MasterStackNode.h"
#include <string>
#include <cmath>

/** @brief
 * Describes the MasterStack class, a class that extends the WindowTreeInterface and that
 * implements a master:stack layout where there is one large window that takes up half of
 * a workspace, and n other windows that equally subdivide the reminaing space.
*/
class MasterStack : public WindowTreeInterface
{
private:
	//pointer to linked list head
	MasterStackNode* head;
	//pointer to linked list tail
	MasterStackNode* tail;
	//area of the given workspace in pixels
	Area area;
	//number of windows in layout
	int numWindows;
	//size of the master window
	int masterSize;
	//orientation of the master window
	bool vertical;
	//ServerInterface pointer (setArea calls enable window management)
	ServerInterface* server;
	//internal render function that makes setArea calls
	void render(MasterStackNode* node, int cumOffset, int depth);

public:
	/// @brief constructs a MasterStack layout for the given ServerInterface* and area
	MasterStack(ServerInterface* server, Area workspaceSize = {0,0, 600, 800});
	/// @brief applies updates to the layout
	virtual void render(ServerInterface* server) override;
	/// @brief adds a window to the layout by id
	virtual void addWindow(long windowID) override;
	/// @brief removes a window from the layout by id
	virtual void remWindow(long windowID) override;
	/// @brief resizes the layout to occupy the given area
	virtual void resize(Area area) override;
	/// @brief rotates the split direction of the layout
	virtual void rotateSplit(long windowID) override;
	/// @brief switch the positions of windows A and B by ID
	virtual void swapWindows(long windowA, long windowB) override;
};