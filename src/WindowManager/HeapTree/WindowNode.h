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
	HeapWindow(const HeapWindow&) = delete;

	~HeapWindow();
	HeapWindow(int windowID = -1, int workspaceID = -1);
	HeapWindow(WindowNode* node);
};