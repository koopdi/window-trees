#pragma once

/***********************************************************
 * Window Tree Interface
 *
 * @brief This abstract class provides an interface for
 *  different layout structures.
 *
 * @file WindowTreeInterface.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */

#include "ServerInterface.h"

class WindowTreeInterface
{
public:
	/// a default constructor to keep the compiler happy
	WindowTreeInterface();
	/**
	 * @brief Update the position of windows in the tree.
	 * @param server The tree calls methods of this server to
	 * update the window positions and size.
	 */
	virtual void render(ServerInterface* server) = 0;
	/**
	 * @brief Tell the tree to manage this window's layout.
	 * @param windowID The ID of the window.
	 */
	virtual void addWindow(long windowID)        = 0;
	/**
	 * @brief Tell the tree to stop managing this window's layout.
	 * @param windowID The ID of the window.
	 */
	virtual void remWindow(long windowID)        = 0;
	/**
	 * @brief I have no idea.
	 * @param area A space, a place, a time...
	 */
	virtual void resize(Area area);
};