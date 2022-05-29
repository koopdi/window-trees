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

#include <string>

using namespace std;

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
	WindowNode* found = nullptr;

	std::function<bool(WindowNode*)> func = [&found, windowID](WindowNode* node) -> bool {
		if (node->isWindow() && node->window->windowID == windowID) {  // check
			return node;  // stop looking
		}
		return true;  //  keep looking
	};

	preOrderTraverse(root, func);
	return found;
}

WindowNode*& WindowTree::getref(int index) {
	index = index - 1; // convert to zero based index
	WindowNode** target = nullptr;
	int num = 0;

	if (index != 0) {

	}

	std::function<bool(WindowNode*)> func = [&target, index, &num](WindowNode* node) -> bool {
		if (num == index) {  // check
			target = &node;
			return false;  // stop looking
		}
		num++;
		return true;  //  keep looking
	};

	preOrderTraverse(root, func);

	WindowNode*& mutableWindowNode = *target;
	return mutableWindowNode;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool WindowTree::isEmpty() const{
	return root == nullptr;
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
 * @brief add a window to the window tree!
 *
 * @param partVertically
 * @param part1Size
 * @param windowID
 */
bool WindowTree::add(bool partVertically, double part1Size, int windowID) {
    if(root == nullptr) {
        root = new WindowNode(partVertically, part1Size, windowID, workspaceID);
		size++;
	} else {
		// get a reference to a pointer to the next node to build off of
		WindowNode*& node = getref(numWindows);

		// add a new parent node and a leaf node, move the old leaf to be a child of the new parent
		WindowNode* temp = node;
		node = new WindowNode();
		node->part1 = temp;
		node->part2 = new WindowNode(partVertically, part1Size, windowID, workspaceID);
	}
	numWindows++;

	bool success = contains(windowID);
	if (!success) throw string("ERROR: fail to add WindowNode to WindowTree");
	return success;

		/*
    } else if (size = 1) {
		WindowNode* temp = root;
		root = new WindowNode();
		size++;
		if (partVertically) {
			root->part1 = temp;
			root->part2 = new WindowNode(partVertically, part1Size, windowID, workspaceID);
		} else {
			root->part2 = temp;
			root->part1 = new WindowNode(partVertically, part1Size, windowID, workspaceID);
		}
		size++;
		numWindows++;
	} else {
		// get a reference to a nullpointer in the correct spot to add the new node
		WindowNode*& node = getref(size);

		// add the new node
		node = new WindowNode(partVertically, part1Size, windowID, workspaceID);
	}
	*/

			/*
				// find level to add node
		int level = 0;
		while (size > ((level + 1) * 2 + 1)) {
			level++;
		}
		// find exact position to add node
		int remainder = size - ((level + 1) * 2 + 1);
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
void WindowTree::postOrderTraverse(WindowNode* node, std::function<void(WindowNode*)> func) const{
    if (node == nullptr) return;

    postOrderTraverse(node->part1, func);
    postOrderTraverse(node->part2, func);
	func(node);
}

WindowTree::~WindowTree(){
	clear();
}

void WindowTree::clear(){
	std::function<void(WindowNode*)> func = [](WindowNode* node) {
		delete node;
	};
	postOrderTraverse(root, func);
}