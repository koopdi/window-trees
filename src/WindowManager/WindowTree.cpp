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
#include "Workspace.h"

#include <iostream>
#include <queue>
#include <string>

using namespace std;

/**
 * @brief Construct a new Window Tree object
 */
WindowTree::WindowTree(Workspace* workspace)
    : workspace(workspace), root(nullptr), last(nullptr){};

int WindowTree::getSize() const { return size; }

/**
 * @brief
 *
 * @return int
 */
int WindowTree::getNumWindows() const { return numWindows; }

/**
 * @brief
 *
 * @param windowID
 * @return WindowNode*
 */
WindowNode* WindowTree::get(int windowID)
{
	WindowNode* found                     = nullptr;

	std::function<bool(WindowNode*)> func = [&found,
	                                         windowID](WindowNode* node) -> bool
	{
		if (node->isWindow() && node->window->windowID == windowID)
		{ // check
			found = node;
			return false; // stop looking
		}
		return true; //  keep looking
	};

	preOrderTraverse(root, func);
	return found;
}

WindowNode*& WindowTree::getRef(int windowID)
{
	WindowNode** target                   = nullptr;

	std::function<bool(WindowNode*)> func = [&target,
	                                         windowID](WindowNode* node) -> bool
	{
		if (node->isWindow() && node->window->windowID == windowID)
		{ // check
			target = &node;
			return false; // stop looking
		}
		return true; //  keep looking
	};

	preOrderTraverse(root, func);

	WindowNode*& mutableWindowNode = *target;
	return mutableWindowNode;
}

WindowNode*& WindowTree::getByIndex(int index)
{
	index               = index - 1; // convert to zero based index
	WindowNode** target = nullptr;
	int num             = 0;

	if (index != 0)
	{
	}

	std::function<bool(WindowNode*)> func =
	    [&target, index, &num](WindowNode* node) -> bool
	{
		if (num == index)
		{ // check
			target = &node;
			return false; // stop looking
		}
		num++;
		return true; //  keep looking
	};

	breadthFirstSearch(root, func);

	if (target == nullptr)
		throw string(
		    "Target not found in getByIndex, can't derefernce nullptr, can't return");
	WindowNode*& mutableWindowNode = *target;

	return mutableWindowNode;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool WindowTree::isEmpty() const { return root == nullptr; }

/**
 * @brief
 *
 * @param windowID
 * @return true
 * @return false
 */
bool WindowTree::contains(int windowID) const
{
	bool contains                         = false;
	/**
	 * @brief find the correct node
	 *
	 * define what we want to do to our nodes as we traverse them
	 * our function must return bool and take in a windowNode pointer
	 * however we can add extra paramaters including return paramaters in the []
	 * brackets */
	std::function<bool(WindowNode*)> func = [&contains,
	                                         windowID](WindowNode* node) -> bool
	{
		if (node->isWindow() && node->window->windowID == windowID)
		{                  // check
			contains = true; // check successful
			return false;    // stop looking
		}
		return true; //  keep looking
	};
	WindowNode* node = root;
	preOrderTraverse(node, func); // find node in preorder
	return contains;              // return success/failure
}

bool WindowTree::contains(WindowNode* target) const
{
	bool contains                         = false;

	std::function<bool(WindowNode*)> func = [&contains,
	                                         target](WindowNode* node) -> bool
	{
		if (node == target)
		{
			contains = true;
			return false;
		}
		return true;
	};

	WindowNode* node = root;
	preOrderTraverse(node, func);
	return contains;
}

/**
 * @brief add a window to the window tree!
 *
 * @param partVertically
 * @param part1Size
 * @param windowID
 */
bool WindowTree::add(bool partVertically, double part1Size, int windowID)
{
	// TODO: need to set partVertically
	std::cout << "WindowTree::add" << endl;
	bool success = false;
	if (root == nullptr)
	{
		root    = new WindowNode(partVertically, part1Size, windowID, workspaceID);
		success = contains(windowID);
		if (success) size++;
	}
	else
	{
		// get a reference to a pointer to the next node to build off of
		WindowNode*& node = getByIndex(numWindows);

		// add a new parent node and a leaf node, move the old leaf to be a child of
		// the new parent
		WindowNode* temp  = node;
		node              = new WindowNode();
		node->part1       = temp;
		node->part2 =
		    new WindowNode(partVertically, part1Size, windowID, workspaceID);
		success = contains(windowID);
		if (success) size += 2;
	}
	if (success) numWindows++;

	if (!success) throw string("ERROR: fail to add WindowNode to WindowTree");
	return success;

	/*
	} else if (size = 1) {
	WindowNode* temp = root;
	root = new WindowNode();
	size++;
	if (partVertically) {
	  root->part1 = temp;
	  root->part2 = new WindowNode(partVertically, part1Size, windowID,
workspaceID); } else { root->part2 = temp; root->part1 = new
WindowNode(partVertically, part1Size, windowID, workspaceID);
	}
	size++;
	numWindows++;
} else {
	// get a reference to a nullpointer in the correct spot to add the new node
	WindowNode*& node = getByIndex(size);

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
 * @brief reorder tree after removal
 *
 * @param node
 * @return true
 * @return false

*//*
bool WindowTree::remove(WindowNode*& node){

	//TODO: this is probably broken

	bool success = false;
	if (node == nullptr) return true;

	int index         = getIndex(node);
	WindowNode*& next = getByIndex(index + 1);
	if (next == nullptr) return true;

	node = next;
	remove(next);
	success &= remove(node);

	if (!success) throw string("ERROR: fail to reorder WindowTree after removal");
	return success;
}
*/

int WindowTree::getIndex(WindowNode* target)
{
	WindowNode* found = nullptr;
	int index         = 0;

	std::function<bool(WindowNode*)> func =
	    [&found, target, &index](WindowNode* node) -> bool
	{
		if (node == target) return false;
		index++;
		return true;
	};

	breadthFirstSearch(target, func);

	bool success = contains(target);
	if (!success)
		throw string("ERROR: getIndex failed to find target WindowNode");
	return index;
}

/**
 * @brief
 *
 * @param windowID
 * @return true
 * @return false
 */
bool WindowTree::remove(int windowID)
{
	bool success        = false;

	WindowNode*& target = getRef(windowID);
	WindowNode* temp    = target;

	WindowNode*& last   = getByIndex(size);

	// swap target with the last node and then remove it.
	target              = last;
	last                = temp;
	delete last;
	last    = nullptr;

	success = !contains(windowID);
	if (success) size--;
	if (!success)
		throw string("ERROR: fail to remove WindowNode from WindowTree");
	return success;
}

/**
 * @brief
 *
 * @param node
 * @param func
 */
void WindowTree::preOrderTraverse(WindowNode* node, forEachNode func) const
{
	if (node == nullptr) return;
	// run the function and save result
	bool keepGoing = func(node);
	if (keepGoing)
	{
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
void WindowTree::inOrderTraverse(WindowNode* node,
                                 std::function<bool(WindowNode*)> func) const
{
	if (node == nullptr) return;

	inOrderTraverse(node->part1, func);
	bool keepGoing = func(node);
	if (keepGoing)
	{
		inOrderTraverse(node->part2, func);
	}
}

/**
 * @brief
 *
 * @param node
 * @param func
 */
void WindowTree::postOrderTraverse(WindowNode* node, forEachNode func) const
{
	if (node == nullptr) return;

	postOrderTraverse(node->part1, func);
	postOrderTraverse(node->part2, func);
	func(node);
}

WindowTree::~WindowTree() { clear(); }

void WindowTree::clear()
{
	forEachNode func = [](WindowNode* node) -> bool { delete node; };
	postOrderTraverse(root, func);
}

void WindowTree::breadthFirstSearch(WindowNode* node,
                                    std::function<bool(WindowNode*)> func)
{
	queue<WindowNode*> levelOrder;
	QueueTree(root, levelOrder);

	while (!levelOrder.empty())
	{
		WindowNode* node = levelOrder.front();
		func(node);
		levelOrder.pop();
	}
}

int WindowTree::height(WindowNode* node)
{
	if (node == nullptr) return 0;

	int left  = height(node->part1);
	int right = height(node->part2);

	if (left > right)
	{
		return (left + 1);
	}
	else
	{
		return (right + 1);
	}
}

void WindowTree::QueueTree(WindowNode* root, queue<WindowNode*>& levelOrder)
{
	int treeHeight = height(root);
	for (int i = 1; i <= treeHeight; i++)
	{
		queueLevel(root, i, levelOrder);
	}
}

void WindowTree::queueLevel(WindowNode* node,
                            int level,
                            queue<WindowNode*>& levelOrder)
{
	if (node == nullptr) return;
	if (level == 1) levelOrder.push(node);
	else if (level > 1)
	{
		queueLevel(node->part1, level - 1, levelOrder);
		queueLevel(node->part2, level - 1, levelOrder);
	}
}

// work in progress ******************************

int WindowTree::calculateHeight(WindowNode* node, int windowID, double height)
{
	// TODO: fix this

	if (node == nullptr) return 0;
	if (node->isWindow() && (node->window->windowID == windowID))
	{
		return height;
	}
	else if (node->partVertically)
	{
		calculateHeight(node->part1, windowID, (height * node->part1Size));
		calculateHeight(node->part2, windowID, (height * (100. - node->part1Size)));
	}
	else
	{
		calculateHeight(node->part1, windowID, height);
		calculateHeight(node->part2, windowID, height);
	}
	return 0;
}

// Point WindowTree::getCoordinate(WindowNode* node, int windowID, int height,
// int width)

Point WindowTree::getCoordinate(int windowID)
{
	Point coordinate({0, 0});
	double height = workspace->getHeight();
	double width  = workspace->getWidth();

	// coordinate = getCoordinate(root, windowID, height, width);

	/*
	  std::function<bool(WindowNode*)> func = [&height, &width,
	  windowID](WindowNode* node) -> bool { if (node->partVertically) { height =
	  height * node->part1Size;

	    } else{
	      height =
	    }

	    if (node->isWindow() && node->window->windowID == windowID) {  // check
	      if (node == nullptr) return false;
	      return false;  // stop looking
	    }
	    return true;  //  keep looking
	  };


	  preOrderTraverse(root, func);
	*/
	return coordinate;
}

// work in progress ******************************