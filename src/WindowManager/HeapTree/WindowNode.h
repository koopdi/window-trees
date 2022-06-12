#pragma once

/**
 * @file WindowNode.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */

#include "types.h"
#include <unordered_set>



//This code defines a WindowPane struct, which represents a window pane in a window.
//It has fields for the pane's ID, tags, and workspace ID. The code also defines functions
//for adding and removing tags from the pane, and for checking if the pane has a given tag.
struct WindowPane {
	std::unordered_set<int> tags;
	int windowID;

	WindowPane(int windowID = -1, int workspaceID = -1);
	bool hasTag(int tag);
	bool addTag(int tag);
	bool removeTag(int tag);
};


//This code defines a data structure for a window node. A window node is a data structure that
//represents a window in a windowing system. The window node has fields for a window ID, a
//workspace ID, and a pointer to a window pane. The window node also has fields for a boolean
//value that indicates whether the window is split vertically or horizontally, a double value
//that represents the size of the first part of the window, and pointers to the first and
//second parts of the window.
struct WindowNode {
	bool partVertically;
	double part1Size;
	WindowPane window;
	WindowNode* part1;
	WindowNode* part2;

	WindowNode(int windowID = -1, int WorkspaceID = -1);

	bool isWindow();
};

//This code creates a HeapWindow object. The HeapWindow object represents a window in the heap.
//The windowID and workspaceID are used to identify the window. The node is used to store the
//window in the heap.
struct HeapWindow {
	Area area;
	WindowNode* node;
	/// This object does not support copy construction.
	HeapWindow(const HeapWindow&) = delete;
	/// Free this HeapWindow's WindowNode
	~HeapWindow();

	 /// @brief Construct a new Heap Window object
	 /// @param windowID The ID of the server window to add.
	 /// @param workspaceID The ID of the workspace the window is on.
	HeapWindow(int windowID = -1, int workspaceID = -1);
	/// @brief An existing window node to add.
	/// @note This HeapWindow will manage the memory of the passed in node.
	HeapWindow(WindowNode* node);
};