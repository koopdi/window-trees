/**
 * @file WindowTree.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */
#pragma once

#include <functional>
#include <queue>

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

	// private methods ----------------------------------------

	void preOrderTraverse(WindowNode* node,
	                      const std::function<bool(WindowNode*)>& func) const;

	WindowNode*& getRef(int windowID);

	void inOrderTraverse(WindowNode* node,
	                     std::function<bool(WindowNode*)> func) const;

	void postOrderTraverse(WindowNode* node,
	                       std::function<void(WindowNode*)> func) const;

	void breadthFirstSearch(WindowNode* node,
	                        std::function<bool(WindowNode*)> func);

	int calculateHeight(WindowNode* node, int windowID, double height);

	WindowNode*& getByIndex(int index);

	bool remove(WindowNode*& node);

	int height(WindowNode* node);

	void QueueTree(WindowNode* root, std::queue<WindowNode*>& levelOrder);

	void
	queueLevel(WindowNode* node, int level, std::queue<WindowNode*>& levelOrder);

	int getIndex(WindowNode* target);
};