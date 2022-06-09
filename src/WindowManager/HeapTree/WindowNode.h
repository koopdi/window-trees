#pragma once

/**
 * @file WindowNode.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */

#include "types.h"
#include <unordered_set>

struct WindowPane {
	std::unordered_set<int> tags;
	int windowID;

	WindowPane(int windowID = -1, int workspaceID = -1);
	bool hasTag(int tag);
	bool addTag(int tag);
	bool removeTag(int tag);
};

struct WindowNode {
	bool partVertically;
	double part1Size;
	WindowPane window;
	WindowNode* part1;
	WindowNode* part2;

	WindowNode(int windowID = -1, int WorkspaceID = -1);

	bool isWindow();
};

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