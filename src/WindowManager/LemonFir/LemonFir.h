#pragma once

/***********************************************************
 * Class Lemon Fir
 * The growth tips taste like lemon.
 * *********************************************************
 * @file LemonFir.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */

#include "ServerInterface.h"


// #include "WindowManager.h"

class LemonFir //: public WindowManager
{
public:
	LemonFir(ServerInterface* server);

	void update(ev::Event& ev);

private:
	/// A pointer to the server.
	ServerInterface* server;
};

/**
 * @brief A tangy non-citrous alpine zest.
 *
	Each window occupies a leaf node, referred to as a WindowPane.

	The parent of a WindowPane is a WindowNode and
	 each of those WindowNodes may also have a parent.

	WindowNodes bifurcate space either vertically or horizontally,
	 depending on their internal state.

	The panes are laid out by walking the tree and
	 placing nodes either left/up or right/down.
	 the available space is halved each time a pane is placed.

	Automatic modes of split orientation include;
	 Every Other - a child node splits opposite it's parent.
	 Minimum Perimeter - the split angle is chosen to make the
	  children as square as possible.
 *
 */