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
	/**
	 * @brief Update the position of windows in the tree.
	 * @param server The tree calls methods of this server to
	 * update the window positions and size.
	 */
	virtual void render(ServerInterface* server) = 0;
	/**
	 * @brief Tell the tree to manage a window's layout.
	 * @param windowID A window ID.
	 */
	virtual void addWindow(long windowID)        = 0;
	/**
	 * @brief Tell the tree to stop managing a window's layout.
	 * @param windowID A window ID.
	 */
	virtual void remWindow(long windowID)        = 0;
	/**
	 * @brief Reverse the split angle of this windows parent.
	 * @param windowID A window ID.
	 */
	virtual void rotateSplit(long windowID)      = 0;
	/**
	 * @brief I have no idea.
	 * @param area A space, a place, a time...
	 */
	virtual void resize(Area area)               = 0;
	// /**
	//  * @brief Set the Screen this tree renders to.
	//  * @param screenID A screen ID.
	//  */
	// virtual void setScreen(long screenID) = 0;
};