/**
 * @file WindowNode.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "WindowNode.h"

/**
 * @brief Construct a new Window Pane object
 *
 * @param windowID
 * @param workspaceID
 */
WindowPane::WindowPane(int windowID, int workspaceID) : windowID(windowID) {
	addTag(workspaceID);
}

/**
 * @brief
 *
 * @param tag
 * @return true
 * @return false
 */
bool WindowPane::hasTag(int tag) {
	return tags.count(tag);
}

/**
 * @brief
 *
 * @param tag
 * @return true
 * @return false
 */
bool WindowPane::addTag(int tag) {
	tags.insert(tag);
	return hasTag(tag);
}

/**
 * @brief
 *
 * @param tag
 * @return true
 * @return false
 */
bool WindowPane::removeTag(int tag) {
	tags.erase(tag);
	return !hasTag(tag);
}

/**
 * @brief Construct a new Window Node:: Window Node object
 *
 * @param partVertically
 * @param windowID
 * @param part1Size
 */
WindowNode::WindowNode(){
	WindowNode(0, 0);
}

WindowNode::WindowNode (bool partVertically, double part1Size)
	: partVertically(partVertically), part1Size(part1Size),
	window(nullptr), part1(nullptr), part2(nullptr) {}

WindowNode::WindowNode (bool partVertically, double part1Size, int WindowID, int WorkspaceID)
	: partVertically(partVertically), part1Size(part1Size), part1(nullptr), part2(nullptr) {
	window = new WindowPane(WindowID, WorkspaceID);
}

bool WindowNode::isWindow() {
	return window != nullptr;
}

WindowNode::~WindowNode() {
	if (window != nullptr) {
		delete window; // no memory leaks
	}
}