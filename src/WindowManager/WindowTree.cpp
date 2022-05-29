/**
 * @file WindowTree.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "WindowTree.h"

/**
 * @brief Construct a new Window Tree:: Window Tree object
 *
 */
WindowTree::WindowTree() {};

/**
 * @brief
 *
 * @return int
 */
int WindowTree::getSize() const {
    return size;
}

/**
 * @brief
 *
 * @return int
 */
int WindowTree::getNumWindows() const {
	return numWindows;
}

/**
 * @brief
 *
 * @param windowID
 * @return WindowNode*
 */
WindowNode* WindowTree::get(int windowID) {
	return 0;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool WindowTree::isEmpty() const{
	return 0;
}

/**
 * @brief
 *
 * @param windowID
 * @return true
 * @return false
 */
bool WindowTree::contains(int windowID) const {
	bool contains = false;
	/**
	 * @brief find the correct node
	 *
	 * define what we want to do to our nodes as we traverse them
	 * our function must return bool and take in a windowNode pointer
	 * however we can add extra paramaters including return paramaters in the [] brackets */
	std::function<bool(WindowNode*)> func = [&contains, windowID](WindowNode* node) -> bool {
		if (node->isWindow() && node->window->windowID == windowID) {  // check
			contains = true;  // check successful
			return false;  // stop looking
		}
		return true;  //  keep looking
	};
	WindowNode* node = root;
	preOrderTraverse(node, func);  // find node in preorder
	return contains;  // return success/failure
}

/**
 * @brief
 *
 * @param partVertically
 * @param windowID
 * @param part1Size
 * @return true
 * @return false
 */
bool WindowTree::add(bool partVertically, int windowID, double part1Size) {
	add(root, partVertically, windowID, part1Size);
}

/**
 * @brief private helper function for adding window nodes
 *
 * @param node
 * @param partVertically
 * @param windowID
 * @param part1Size
 */
void WindowTree::add(WindowNode*& node, bool partVertically, int windowID, double part1Size) {
	//TODO: will WindowIDs be generated in the WindowTree or passed in?
    if(node == nullptr) {
        node = new WindowNode(partVertically, part1Size);
		size++;
    } /* else if (val > node->data) {
        add(node->right, val);
    } else if (val < node->data) {
        add(node->left, val);
    }
	*/
}

/**
 * @brief
 *
 * @param windowID
 * @return true
 * @return false
 */
bool WindowTree::remove(int windowID) {
    size--;
    // TODO: remove node
	return 0;
}

/**
 * @brief
 *
 * @param node
 * @param func
 */
void WindowTree::preOrderTraverse(WindowNode* node, const std::function<bool(WindowNode*)>& func) const{
    if (node == nullptr) return;
    // run the function and save result
    bool keepGoing = func(node);
    if (keepGoing) {
      // recurse
    preOrderTraverse(node->part1, func);
    preOrderTraverse(node->part2, func);
	}
}

/**
 * @brief
 *
 * @param node
 * @param func
 */
void WindowTree::inOrderTraverse(WindowNode* node, std::function<bool(WindowNode*)> func) const{
    if (node == nullptr) return;

    inOrderTraverse(node->part1, func);
	bool keepGoing = func(node);
	if (keepGoing) {
    inOrderTraverse(node->part2, func);
	}
}

/**
 * @brief
 *
 * @param node
 * @param func
 */
void WindowTree::postOrderTraverse(WindowNode* node, std::function<bool(WindowNode*)> func) const{
    if (node == nullptr) return;

    postOrderTraverse(node->part1, func);
    postOrderTraverse(node->part2, func);
	func(node);
}
