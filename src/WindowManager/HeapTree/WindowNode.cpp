/**
 * @file WindowNode.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */

#include "WindowNode.h"
#include <iostream>

// This code creates a new HeapWindow object with the given window ID and workspace ID.
HeapWindow::HeapWindow (int windowID, int workspaceID)
{
	this->node = new WindowNode(windowID, workspaceID);
}

// this constructs a HeapWindow from a WindowNode
HeapWindow::HeapWindow (WindowNode* node)
{
	this->node = node;
}

/**
 * @brief Construct a new Window Node:: Window Node object
 *
 * @param windowID the ID for the window
 * @param workspaceID  the ID  for the workspace
 */
WindowNode::WindowNode(int windowID, int workspaceID)
: 	window(WindowPane(windowID, workspaceID)),
	part1(nullptr),
	part2(nullptr),
	partVertically(0),
	part1Size(50)
{}

/**
 * @brief Construct a new Window Pane object
 * @param windowID The ID of the window to place in this pane.
 * @param workspaceID The ID of the workspace to place this pane on.
 */
WindowPane::WindowPane(int windowID, int workspaceID) : windowID(windowID)
{
	addTag(workspaceID);
}

// returns if a window in within a workspace specieifed by a tag (workspaceID).
bool WindowPane::addTag(int tag)
{
	tags.insert(tag);
	return hasTag(tag);
}

// returns if a node is a window.
bool WindowNode::isWindow() {
	return window.windowID != -1;
}

// removes a tag from the window
bool WindowPane::removeTag(int tag)
{
	tags.erase(tag);
	return !hasTag(tag);
}

// deconstruct the window
HeapWindow::~HeapWindow()
{
	if (node != nullptr)
	{
		delete node; // no memory leaks
	}
}