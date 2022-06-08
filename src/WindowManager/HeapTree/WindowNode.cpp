/**
 * @file WindowNode.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */

#include "WindowNode.h"
#include <iostream>

Window::Window (int windowID, int workspaceID)
{
	this->node = new WindowNode(int windowID, int workspaceID);
}

Window::Window (WindowNode* node)
{
	this->windowID = node->window.windowID;
	this->node = node;
}

WindowNode::WindowNode(int WindowID, int WorkspaceID)
{
	std::cout << "WindowNode Constructor" << std::endl;

	this->window = WindowPane(int windowID, int workspaceID);
	this->part1 = nullptr;
	this->part2 = nullptr;
	partVertically = 0;
	part1Size = 50;
}

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

bool WindowNode::isWindow() {
	return window.windowID != -1;
}

bool WindowPane::removeTag(int tag)
{
	tags.erase(tag);
	return !hasTag(tag);
}

bool WindowNode::isWindow() { return window != nullptr; }

Window::~Window()
{
	if (node != nullptr)
	{
		delete node; // no memory leaks
	}
}