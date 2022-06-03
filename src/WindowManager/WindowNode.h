/**
 * @file WindowNode.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */

#pragma once

#include <unordered_set>

struct WindowPane
{
	std::unordered_set<int> tags;
	int windowID;

	WindowPane(int windowID, int workspaceID);
	bool hasTag(int tag);
	bool addTag(int tag);
	bool removeTag(int tag);
};

struct WindowNode
{
	bool partVertically;
	double part1Size;
	WindowPane* window;
	WindowNode* part1;
	WindowNode* part2;

	WindowNode(bool partVertically = false,
	           int windowID        = -1,
	           int workspaceID     = -1);

	~WindowNode();

	bool isWindow();
};