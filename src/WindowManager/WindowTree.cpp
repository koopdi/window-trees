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

WindowTree::WindowTree(Workspace* workspace) {
		workspaceID = (long long)(workspace);
		this->workspace = workspace;
		last = nullptr;
		heap.push_back(new WindowNode());
		root = heap[0];
		size = 1;
		numWindows = 0;
	};

int WindowTree::getSize() const { return size; }

int WindowTree::getNumWindows() const { return numWindows; }

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

// takes a binary tree and a string of spaces and prints the tree's
// right subtree with four more spaces in front of all its nodes,
// this node's data and then its left subtree with an additional
// four spaces before each node.
void WindowTree::printSidewaysHelper(WindowNode* root, string spaces) {
    if(root != nullptr) {
        printSidewaysHelper(root->part2, spaces + "    ");
        cout << spaces << (root->isWindow() ? root->window->windowID : (long long)root) << endl;
        printSidewaysHelper(root->part1, spaces + "    ");
    }
}

// prints out the tree stored in the passed in root with its root node on the
// left and each child node indented four spaces further. The right side of
// the tree is on the top and the left side on the bottom with each node on
// its own line
void WindowTree::printSideways(WindowNode* root) {
    printSidewaysHelper(root, "");
}


void WindowTree::printHeap(vector<WindowNode*> heap) {
	int num = 0;
	for (WindowNode* node: heap) {
		cout << num << ": ";
		num++;
		cout << (node->isWindow() ? node->window->windowID : (long long)node) << endl;
	}
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
	std::cout << "WindowTree::add" << endl;

	cout << "numWindows: " << numWindows << endl;
	bool success = false;
	if (numWindows < 2)
	{
		heap.push_back(new WindowNode(0, 0, windowID, workspaceID));
		if (numWindows == 0)
		{
			root->part1Size = 100.;
			root->part1 = heap.back();
		}
		else
		{
			root->part1Size = part1Size;
			root->part2 = heap.back();
		}
		success = contains(windowID);

		if (!success) throw string("failed to add first node");
	}
	else
	{
		// add node to heap
		heap.push_back(new WindowNode(partVertically, part1Size, windowID, workspaceID));

		cout << endl;
		printSideways(root);
		cout << endl;
		printHeap(heap);
		cout << endl;

		cout << "size: " << size << endl;
		WindowNode* parentOfTarget = heap[(size - 1) / 2];

		if (parentOfTarget->part1 == nullptr)
		{
			parentOfTarget->part1 = heap.back();
		}
		else
		{
			parentOfTarget->part2 = heap.back();
		}

		success = contains(windowID);

	}
	cout << endl;
	printSideways(root);
	cout << endl;
	printHeap(heap);
	cout << endl;

	if (success)
	{
		numWindows++;
		size++;
	}
	else
	{
		throw string("ERROR: fail to add WindowNode to WindowTree");
	}

	cout << "size: " << size << endl;

	return success;
}


/**
 * @brief
 *
 * @param windowID
 * @return true
 * @return false
 */
bool WindowTree::remove(int windowID)
// this fucntion is bugged if the node trying to be removed has 1 child
// it works if the node has no children or two children.
// it does not crash if there is no such node
{
	bool success;
	WindowNode* found = get(windowID);
	if (found == nullptr) return false;

	int index = 0;
	for (WindowNode* node: heap) {
		if (node == found) break;
		index++;
	}

	WindowNode* tempLeft;
	WindowNode* tempRight;

	tempLeft = heap[index]->part1;
	tempRight = heap[index]->part2;
	WindowNode* parentOfTarget = heap[(index - 1) / 2];

	if (parentOfTarget->part1 == heap[index]) {
		//parentOfTarget->part1 = heap.back();
	} else {
		parentOfTarget->part2 = heap.back();
	}

	heap[index] = heap.back();
	if (heap[index]->part1 != nullptr) // 1 left child case
		heap[index]->part1 = tempLeft;
	if (heap[index]->part2 != nullptr)
		heap[index]->part2 = tempRight; // 1 right child case

	cout << endl;
	printSideways(root);
	cout << endl;
	printHeap(heap);
	cout << endl;

	WindowNode* parentOfLast = heap[(size - 2) / 2];


	if (parentOfLast->part2 == heap.back())
	// zero child case: check part two first
	{
		parentOfLast->part2 = nullptr;
	}
	else
	{
		parentOfLast->part1 = nullptr;
	}

	success = !contains(windowID);
	if (success)
	{
		size--;
		heap.pop_back();
	}

	cout << endl;
	printSideways(root);
	cout << endl;
	printHeap(heap);
	cout << endl;

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
	forEachNode func = [this](WindowNode* node) -> bool { delete node; return true;};
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