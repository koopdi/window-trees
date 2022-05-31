/**
 * @file WindowTree.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */
#pragma once

#include <functional>
#include <queue>
#include <vector>
#include <string>

#include "WindowNode.h"
#include "types.h"

class Workspace;

class WindowTree
{
public:
	// public methods ----------------------------------------

	/**
	 * @brief Construct a new Window Tree object
	 */
	WindowTree(Workspace* workspace);

	Point getCoordinate(int windowID);

	WindowNode* get(int windowID);

	bool add(bool partVertically, double part1Size, int windowID);

	bool remove(int windowID);

	bool isEmpty() const;

	bool contains(int windowID) const;

	bool contains(WindowNode* node) const;

	int getSize() const;

	int getNumWindows() const;

	void clear();

	~WindowTree();

private:
	// private attributes ------------------------------------
	Workspace* workspace;

	// the number of windows
	int numWindows;

	int workspaceID;

	// the size of the tree
	int size;

	// a pointer to the root node of the tree
	WindowNode* root;

	// a pointer to the most recently added node
	WindowNode* last;

	std::vector<WindowNode*> heap;

	// private methods ---------------------------------------

	/// A function that is passed to a xyzTraverse function.
	using forEachNode = std::function<bool(WindowNode*)>;

	void printSideways(WindowNode* root);

	void printSidewaysHelper(WindowNode* root, std::string spaces);

	void preOrderTraverse(WindowNode* node, forEachNode func) const;

	WindowNode*& getRef(int windowID);

	void inOrderTraverse(WindowNode* node, forEachNode func) const;

	void postOrderTraverse(WindowNode* node, forEachNode func) const;

	void breadthFirstSearch(WindowNode* node, forEachNode func);

	int calculateHeight(WindowNode* node, int windowID, double height);

	WindowNode*& getByIndex(int index);

	bool remove(WindowNode*& node);

	int height(WindowNode* node);

	/**
	 * @brief Holds pointers to nodes in level order.
	 * @param root The root of the tree to build queue from.
	 * @param levelOrder A queue of window nodes inlevel order from top to bottom.
	 */
	void QueueTree(WindowNode* root, std::queue<WindowNode*>& levelOrder);

	/**
	 * @brief A recursive helper for QueueTree
	 * @param node The current node.
	 * @param level The target level to enqueue.
	 * @param levelOrder A queue of window nodes inlevel order from top to bottom.
	 */
	void
	queueLevel(WindowNode* node, int level, std::queue<WindowNode*>& levelOrder);

	int getIndex(WindowNode* target);
};