/**
 * @file WindowTree.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <functional>

#include "WindowNode.h"

/**
 * @brief
 *
 */
class WindowTree {
public:
	// public methods ----------------------------------------

	/**
	 * @brief Construct a new Window Tree object
	 *
	 */
    WindowTree();

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
	 * @param windowID
	 * @param part1Size
	 * @return true
	 * @return false
	 */
    bool add(bool partVertically, int windowID, double part1Size);

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

private:
	// private attributes ------------------------------------

	// the number of windows
	int numWindows;

	// the size of the tree
    int size;

	// a pointer to the root node of the tree
    WindowNode* root;

	// private methods ----------------------------------------

	/**
	 * @brief
	 *
	 * @param node
	 * @param func
	 */
    void preOrderTraverse(WindowNode* node, const std::function<bool(WindowNode*)>& func) const;

	/**
	 * @brief
	 *
	 * @param node
	 * @param func
	 */
    void inOrderTraverse(WindowNode* node, std::function<bool(WindowNode*)> func) const;

	/**
	 * @brief
	 *
	 * @param node
	 * @param func
	 */
    void postOrderTraverse(WindowNode* node, std::function<bool(WindowNode*)> func) const;

	/**
	 * @brief
	 *
	 * @param node
	 * @param partVertically
	 * @param windowID
	 * @param part1Size
	 */
	void add(WindowNode*& node, bool partVertically, int windowID, double part1Size);
};