#pragma once

#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

#include "ServerInterface.h"
#include "WindowTreeInterface.h"
#include "WindowNode.h"
#include "types.h"

class Workspace;

/**
 * @brief this class is a heap like tree that stores windows
 *
 */
class HeapTree : public WindowTreeInterface
{
public:
	/**
	 * @brief Construct a new Heap Tree object
	 *
	 */
	HeapTree();

	/**
	 * @brief render all windows in the tree, required by WindowTreeInterface.
	 *
	 * @param server // an abstract interface for displaying windows
	 */
	void render(ServerInterface* server) override;

	/**
	 * @brief add a window to the tree. required by WindowTreeInterface.
	 *
	 * @param windowID the ID for a window
	 */
	void addWindow(long windowID) override;

	/**
	 * @brief remove a window from the tree. required by WindowTreeInterface.
	 *
	 * @param windowID
	 */
	void remWindow(long windowID) override;

	/**
	 * @brief not implemented. required by WindowTreeInterface.
	 *
	 * @param area
	 */
	void resize(Area area) override;

	/**
	 * @brief not implemented. required by WindowTreeInterface.
	 *
	 * @param windowID an ID for the window
	 */
	void rotateSplit(long windowID);


	/**
	 * @brief not implemented. required by WindowTreeInterface.
	 *
	 * @param windowA a window to be swaped
	 * @param windowB the second window to be swaped
	 */
	void swapWindows(long windowA, long windowB) override;


	/**
	 * @brief update the displayed windows
	 *
	 */
	void update();

	/**
	 * @brief Construct a new Heap Tree object
	 *
	 * @param server // an abstract interface for displaying windows
	 */
	HeapTree(ServerInterface* server);

private:
	Area area;						// the area of the workspace the tree's windows are on
	int numWindows;  				// the number of windows
	int workspaceID;				// the ID for the Workspace that owns the tree
	int size;  						// the size of the tree
	WindowNode* root;   			// a pointer to the root node of the tree
	WindowNode* last; 				// a pointer to the most recently added node
	std::vector<HeapWindow*> heap;	// a heap of Windows with WindowNodes that is in sync with the tree
	ServerInterface* server;		// an abstract interface for displaying windows

	/**
	 * @brief return if the tree is empty
	 *
	 * @return true
	 * @return false
	 */
	bool isEmpty() const;

	/**
	 * @brief return if a window is in the tree
	 *
	 * @param windowID The ID for a window
	 * @return true
	 * @return false
	 */
	bool contains(int windowID) const;

	/**
	 * @brief return if a window is in the tree
	 *
	 * @param node
	 * @return true
	 * @return false
	 */
	bool contains(WindowNode* node) const;

	/**
	 * @brief return the number of nodes in the tree
	 *
	 * @return int
	 */
	int getSize() const;

	/**
	 * @brief return the Number of windows
	 *
	 * @return int
	 */
	int getNumWindows() const;

	/**
	 * @brief a function for debuging and isplaying the contents of the heap
	 *
	 * @param heap a vector of windows
	 */
	void printHeap(const std::vector<HeapWindow*>& heap) const;
	void printSideways(WindowNode* root) const;
	void printSidewaysHelper(WindowNode* root, std::string spaces) const;
	//void preOrderTraverse(WindowNode* node, forEachNode func) const;
	//void inOrderTraverse(WindowNode* node, forEachNode func) const;
	//void postOrderTraverse(WindowNode* node, forEachNode func) const;
	bool add(int windowID);
	bool remove(int windowID);

	/// A function that is passed to a xyzTraverse function.
	using forEachNode = std::function<bool(WindowNode*)>;
};