/**
 * @file WindowNode.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <unordered_set>

/**
 * @brief
 *
 */
struct WindowPane
{
	std::unordered_set<int> tags;
	int windowID;

	WindowPane(int windowID, int workspaceID);
	bool hasTag(int tag);
	bool addTag(int tag);
	bool removeTag(int tag);
};

/**
 * @brief
 *
 */
struct WindowNode
{
	bool partVertically;
	double part1Size;
	WindowPane* window;
	WindowNode* part1;
	WindowNode* part2;

	WindowNode();
	WindowNode(bool partVertically, double part1Size);
	WindowNode(bool partVertically,
	           double part1Size,
	           int windowID,
	           int workspaceID);

	~WindowNode();

	bool isWindow();
};