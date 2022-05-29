/**
 * @file Workspace.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "WindowNode.h"
#include "types.h"
#include "WindowTree.h"

class WindowTree;

/**
 * @brief
 *
 */
class Workspace {
public:
	// public methods ----------------------------------------

	/**
	 * @brief Construct a new Workspace object
	 *
	 */
    Workspace();

	/**
	 * @brief Get the Height object
	 *
	 * @return int
	 */
    int getHeight() const;

	/**
	 * @brief Get the Width object
	 *
	 * @return int
	 */
    int getWidth() const;

	/**
	 * @brief Get the Position object
	 *
	 * @return Point
	 */
    Point getPosition() const;

	/**
	 * @brief Get the Num Windows object
	 *
	 * @return int
	 */
    int getNumWindows() const;

private:
	// private attributes ------------------------------------

	// a pointer to the window tree
    WindowTree* tree;

	// the height of the workspace
    int height;

	// the width of the workspace
    int width;

	int workspaceID;

	// the number of windows in the workspace
    int numWindows;

	// a point representing the position of the top left corner of the workspace
    Point position;

	// private methods ----------------------------------------

	/**
	 * @brief Set the Height object
	 *
	 * @param height
	 */
    void setHeight(int height);

	/**
	 * @brief Set the Width object
	 *
	 * @param width
	 */
    void setWidth(int width);

	/**
	 * @brief Set the Position object
	 *
	 * @param position
	 */
    void setPosition(Point position);
	/**
	 * @brief
	 *
	 * @param partVertically
	 * @param windowID
	 * @param part1Size
	 * @return true
	 * @return false
	 */
    bool addWindow(bool partVertically, int windowID, double part1Size);

	/**
	 * @brief
	 *
	 * @param windowID
	 * @return true
	 * @return false
	 */
    bool removeWindow(int windowID);
};