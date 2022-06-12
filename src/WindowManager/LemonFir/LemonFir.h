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

	// WindowTreeInterface -----------------------------------
	/// Add a window to this tree.
	/// \param windowID The ID of the window to add.
	virtual void addWindow(long windowID) override;

	/// Remove a window from this tree.
	/// \param windowID The ID of the window to remove.
	virtual void remWindow(long windowID) override;

	/**
	 * @brief Update the size and position of all windows in this tree.
	 * @param server The graphics and input system object.
	 */
	virtual void render(ServerInterface* server) override;

	/**
	 * @brief Notify this layout that the screen dimensions have changed.
	 * @param area The new screen dimensions.
	 */
	virtual void resize(Area area) override;

	/**
	 * @brief Rotate a window container.
	 * @param windowID The ID of a window in the container to rotate.
	 */
	virtual void rotateSplit(long windowID) override;

	/**
	 * @brief Swap the position of 2 windows.
	 * @param windowA A window to swap.
	 * @param windowB Another window to swap.
	 */
	virtual void swapWindows(long windowA, long windowB) override;
	virtual void swapGroups(long windowA, long windowB);

private:
	/// A pointer to the server.
	ServerInterface* server;
	/// The screen this tree is on.
	long screen;
	/// The root of the underlying tree.
	NodePtr tree;

	// Private Methods ---------------------------------------
	/// Get the next open spot in the treee.
	NodePtr& nextOpen();
	/// Recursive helper for nextopen.
	/// \param node The current node.
	NodePtr& nextOpen(NodePtr& node);

	/// Display the contents of this tree.
	void print();
	/// Recursive helper for print.
	/// \param node the current node in the tree.
	void print(NodePtr node);

	/// Recursively traverse the tree and layout the panes.
	/// Area by reference.
	void render(NodePtr node, Area& space);

	/// Recursively traverse the tree and remove
	/// panes with a matching ID.
	void remove(NodePtr& node, long windowID);

	/// find the parent of windowID
	NodePtr* getParent(long targetID);

	/**
	 * @param node The current node.
	 * @param windowID The window to get the parent of.
	 * @return PanePtr The parent of the window or
	 *  Null Pointer if no parent of that window exists.
	 */
	NodePtr* getParent(NodePtr* node, long targetID);

	/**
	 * @brief Get the Tree Pane object.
	 * @param targetID The ID of the window in the pane to get.
	 * @return NodePtr* A raw pointer to a smart pointer to a pane.
	 */
	NodePtr* getTreePane(long targetID);
	/**
	 * @brief Recursive helper for getTreePane.
	 * @param node The current node
	 * @param targetID The ID of the window in the pane to get.
	 * @return NodePtr* A raw pointer to a smart pointer to a pane.
	 */
	NodePtr* getTreePane(NodePtr* node, long targetID);
};
