#pragma once

/***********************************************************
 * Class Lemon Fir Tree
 * A tangy non-citrous alpine zest.
 * *********************************************************
 * @brief This class implements the tree interface.
 *
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
	// ServerInterFace ---------------------------------------
	LemonFir(ServerInterface* server = nullptr);
	// allow the LemonFir to act as a full window manager for now.
	void update(ev::Event& ev);

	// WindowTreeInterface -----------------------------------
	/// Add a window to this tree.
	/// \param windowID The ID of the window to add.
	virtual void addWindow(long windowID) override;

	/// Remove a window from this tree.
	/// \param windowID The ID of the window to remove.
	virtual void remWindow(long windowID) override;

	virtual void render(ServerInterface* server) override;
	virtual void resize(Area area) override;

	virtual void rotateSplit(long windowID) override;

private:
	/// A pointer to the server.
	ServerInterface* server;
	long screen;
	NodePtr tree;

	// Private Methods ---------------------------------------
	/// Get the next open spot in the treee.
	NodePtr& nextOpen();
	NodePtr& nextOpen(NodePtr& node, int cycles = 0);

	/// Display the contents of this tree.
	void print();
	void print(NodePtr node);

	/// Recursively traverse the tree and layout the panes.
	/// Area by reference.
	void render(NodePtr node, Area& space, bool vSplit = true);

	/// Recursively traverse the tree and remove
	/// panes with a matching ID.
	void remove(NodePtr& node, long windowID);

	/// find the parent of windowID
	NodePtr getParent(long targetID);
	/**
	 * @param node The current node.
	 * @param windowID The window to get the parent of.
	 * @return PanePtr The parent of the window or
	 *  Null Pointer if no parent of that window exists.
	 */
	NodePtr getParent(NodePtr node, long targetID);

	// /// find the parent of this node
	// NodePtr getParent(NodePtr target);
	// /// find the parent of this node
	// NodePtr getParent(NodePtr node, NodePtr target);

};
