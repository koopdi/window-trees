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
	 *
	 */
	WindowTree(Workspace* workspace);

	Point getCoordinate(int windowID);

	/**
	 * @brief
	 *
	 * @param windowID
	 * @return WindowNode*
	 */
	WindowNode* get(int windowID);

	/**
	 * @brief
	 *
	 * @param partVertically
	 * @param part1Size
	 * @param WindowID
	 * @param WorkspaceID
	 * @return true
	 * @return false
	 */
	bool add(bool partVertically, double part1Size, int windowID);

	/**
	 * @brief
	 *
	 * @param windowID
	 * @return true
	 * @return false
	 */
	bool remove(int windowID);

	/**
	 * @brief
	 *
	 * @return true
	 * @return false
	 */
	bool isEmpty() const;

	/**
	 * @brief
	 *
	 * @param windowID
	 * @return true
	 * @return false
	 */
	bool contains(int windowID) const;

	bool contains(WindowNode* node) const;

	/**
	 * @brief Get the Size object
	 *
	 * @return int
	 */
	int getSize() const;

	/**
	 * @brief Get the Num Windows object
	 *
	 * @return int
	 */
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

	/**
	 * @brief
	 *
	 * @param node
	 * @param func
	 */
	void preOrderTraverse(WindowNode* node,
	                      const std::function<bool(WindowNode*)>& func) const;

	/**
	 * @brief
	 *
	 * @param windowID
	 * @return WindowNode*&
	 */
	WindowNode*& getRef(int windowID);

	/**
	 * @brief
	 *
	 * @param node
	 * @param func
	 */
	void inOrderTraverse(WindowNode* node,
	                     std::function<bool(WindowNode*)> func) const;

	/**
	 * @brief
	 *
	 * @param node
	 * @param func
	 */
	void postOrderTraverse(WindowNode* node,
	                       std::function<void(WindowNode*)> func) const;

	void breadthFirstSearch(WindowNode* node,
	                        std::function<bool(WindowNode*)> func);

	int calculateHeight(WindowNode* node, int windowID, double height);

	/**
	 * @brief
	 *
	 * @param windowID
	 * @return WindowNode*
	 */
	WindowNode*& getByIndex(int index);

	bool remove(WindowNode*& node);

	int height(WindowNode* node);

	void QueueTree(WindowNode* root, std::queue<WindowNode*>& levelOrder);

	void
	queueLevel(WindowNode* node, int level, std::queue<WindowNode*>& levelOrder);

	int getIndex(WindowNode* target);
};