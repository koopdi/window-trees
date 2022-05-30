/**
 * @file WindowNode.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */

#include "WindowNode.h"

/**
 * @brief Construct a new Window Pane object
 * @param windowID The ID of the window to place in this pane.
 * @param workspaceID The ID of the workspace to place this pane on.
 */
WindowPane::WindowPane(int windowID, int workspaceID) : windowID(windowID)
{
	addTag(workspaceID);
}

bool WindowPane::hasTag(int tag) { return tags.count(tag); }

bool WindowPane::addTag(int tag)
{
	tags.insert(tag);
	return hasTag(tag);
}

bool WindowPane::removeTag(int tag)
{
	tags.erase(tag);
	return !hasTag(tag);
}

WindowNode::WindowNode() { WindowNode(false, 0); }

WindowNode::WindowNode(bool partVertically, double part1Size)
    : partVertically(partVertically), part1Size(part1Size), window(nullptr),
      part1(nullptr), part2(nullptr)
{
}

WindowNode::WindowNode(bool partVertically,
                       double part1Size,
                       int WindowID,
                       int WorkspaceID)
    : partVertically(partVertically), part1Size(part1Size), part1(nullptr),
      part2(nullptr)
{
	window = new WindowPane(WindowID, WorkspaceID);
}

bool WindowNode::isWindow() { return window != nullptr; }

WindowNode::~WindowNode()
{
	if (window != nullptr)
	{
		delete window; // no memory leaks
	}
}