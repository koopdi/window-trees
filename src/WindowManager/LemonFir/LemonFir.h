#pragma once

/***********************************************************
 * Class Lemon Fir Tree
 * A tangy non-citrous alpine zest.
 * *********************************************************
 * @brief This class implements the tree interface.
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

 * @file LemonFir.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */

#include "WindowTreeInterface.h"

// #include "WindowManager.h"
#include "LemonFirNode.h"
class LemonFir : public WindowTreeInterface
{
public:
	LemonFir(ServerInterface* server = nullptr);
	// allow the LemonFir to act as a full window manager for now.
	void update(ev::Event& ev);

	// WindowTreeInterface
	virtual void render(ServerInterface* server) override;
	virtual void addWindow(long windowID) override;
	virtual void remWindow(long windowID) override;
	virtual void resize(Area area) override;

private:
	/// A pointer to the server.
	ServerInterface* server;
	LemonFirNode* tree;
};
