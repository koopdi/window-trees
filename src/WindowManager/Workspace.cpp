/**
 * @file Workspace.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "Workspace.h"

/**
 * @brief Construct a new Workspace:: Workspace object
 *
 * @param workspaceID
 */
Workspace::Workspace(int workspaceID) {}

/**
 * @brief
 *
 * @return int
 */
int Workspace::getHeight() const {
	return height;
}

/**
 * @brief
 *
 * @return int
 */
int Workspace::getWidth() const {
	return width;
}

/**
 * @brief
 *
 * @return Point
 */
Point Workspace::getPosition() const {
	return position;
}

/**
 * @brief
 *
 * @return int
 */
int Workspace::getNumWindows() const {
	return numWindows;
}

/**
 * @brief
 *
 * @param height
 */
void Workspace::setHeight(int height) {
	this->height = height;
}

/**
 * @brief
 *
 * @param width
 */
void Workspace::setWidth(int width) {
	this->width = width;
}

/**
 * @brief
 *
 * @param position
 */
void Workspace::setPosition(Point position) {
	this->position = position;
}

/**
 * @brief
 *
 * @param partVertically
 * @param windowID
 * @param part1Size
 * @return true
 * @return false
 */
bool Workspace::addWindow(bool partVertically, int windowID, double part1Size) {
	bool success = tree->add(partVertically, windowID, part1Size);
	// if (success) {
	//		TODO: add to map<windowID:set<workspaceID>>
	//		map[windowID];
	// }
	return success;
}

/**
 * @brief
 *
 * @param windowID
 * @return true
 * @return false
 */
bool Workspace::removeWindow(int windowID) {
	bool success = tree->remove(windowID);
	// if (success) {
	//		TODO: add to map<windowID:set<workspaceID>>
	//		map.erase(windowID);
	// }
	return success;
}