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
#include <algorithm>

using namespace std;

/**
 * @brief Construct a new Window Tree:: Window Tree object
 *
 * @param workspace This is the workspace a WindowTree belongs to
 */
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

WindowNode* WindowTree::get(int targetID)
{
	int index = (size - 1) / 2;  // starting here lets us skip parent nodes

	for (;index < heap.size(); index++)
	{
		WindowNode* node = heap[index];
		if (node->window->windowID == targetID)
			return node;
	}

	return nullptr;
}

/**
 * @brief returns if the tree has any windows
 *
 * @return true
 * @return false
 */
bool WindowTree::isEmpty() const { return numWindows == 0; }

/**
 * @brief returns if a windowID is held in the tree
 *
 * @param targetID the WindowID we are searching for
 * @return true
 * @return false
 */
bool WindowTree::contains(int targetID) const
{
	int index = (size - 1) / 2;  // starting here lets us skip parent nodes

	for (;index < heap.size(); index++)
	{
		int foundID = heap.at(index)->window->windowID;
		if (foundID == targetID)
			return true;
	}

	return false;
}

bool WindowTree::contains(WindowNode* target) const
{
	auto it = find(heap.begin(), heap.end(), target);
	return *it == target;
}

// takes a binary tree and a string of spaces and prints the tree's
// right subtree with four more spaces in front of all its nodes,
// this node's data and then its left subtree with an additional
// four spaces before each node.
void WindowTree::printSidewaysHelper(WindowNode* node, string spaces) {
    if(node != nullptr) {
        printSidewaysHelper(node->part2, spaces + "    ");
        cout << spaces << (node->isWindow() ? node->window->windowID : (long long)node) << endl;
        printSidewaysHelper(node->part1, spaces + "    ");
    }
}

// prints out the tree stored in the passed in root with its root node on the
// left and each child node indented four spaces further. The right side of
// the tree is on the top and the left side on the bottom with each node on
// its own line
void WindowTree::printSideways(WindowNode* root) {
    printSidewaysHelper(root, "");
}


WindowNode* WindowTree::getRoot()
{
	return root;
}

void WindowTree::printHeap(vector<WindowNode*> heap) {
	int num = 0;
	for (WindowNode* node: heap) {
		cout << num << ": ";
		num++;
		cout << (node->isWindow() ? node->window->windowID : (long long)node) << endl;
	}
}

void WindowTree::addHelper(int& index, WindowNode*& target, WindowNode*& parentOfTarget)
{
	index = 1;
	parentOfTarget = heap[0];
	target = heap[1];
	WindowNode* next = heap[1];

	while (next->window->windowID == -1)
	{
		parentOfTarget = heap[index - 1];
		target = heap[index];
		next = heap[index + 1];
		index++;
	}

	cout << "index: " << index << endl;
}


/**
 * @brief add a window to the window tree!
 *
 * @param part1Size the size multiplier for the part1 child node
 * @param windowID the ID for the window
 */
bool WindowTree::add(double part1Size, int windowID) // TODO: change part1Size when moving nodes
{
	std::cout << "WindowTree::add" << endl;
	bool success = false;

	if (size <= 2)
	{
		heap.push_back(new WindowNode(1, windowID, workspaceID));
		if (size == 1)
		{
			root->part1Size = 1.;
			root->part1 = heap.back();
		}
		else
		{
			root->part1Size = part1Size;
			root->part2 = heap.back();
		}
		success = contains(windowID);

		if (success)
			size++;
		if (!success)
			throw string("failed to add early node");
	}
	else
	{
		int index = (size - 1) /2;
		// target is the node that will be built off of
		WindowNode* target = heap[(size - 1) / 2];
		// having the parent makes reassigning nodes easier
		WindowNode* parentOfTarget = heap[(index - 1) / 2];

		// one of these will be target
		WindowNode* leftChild = parentOfTarget->part1;  // child of parentOfTarget
		WindowNode* rightChild = parentOfTarget->part2; // child of parentOfTarget

		// nodes always part the opposite of their parents
		bool partVertically = !(target->partVertically);

		// each add after node 2 requires 2 nodes, a parent and window
		WindowNode* newParent = new WindowNode(partVertically);
		WindowNode* newWindow = new WindowNode(partVertically, windowID, workspaceID);

		newParent->part1Size = part1Size;		// set part1size

		heap.push_back(newParent);		// add new nodes to heap
		heap.push_back(newWindow);

		// cout << "target: " << target->window->windowID << endl;
		// cout << "parentOfTarget: " << parentOfTarget->window->windowID << endl;
		// cout << "tempLeft: " << leftChild->window->windowID << endl;
		// cout << "tempRight: " << rightChild->window->windowID << endl;
		// cout << "newParent: " << newParent->window->windowID << endl;
		// cout << " newWindow: " <<  newWindow->window->windowID << endl;

		// **** modify tree ***************
		if (leftChild == target)  // check which child is our target for building from
		{
			newParent->part1 = leftChild;  			// swap target with newParent
			parentOfTarget->part1 = newParent;
		}
		else
		{
			newParent->part1 = rightChild;			// swap target with newParent
			parentOfTarget->part2 = newParent;
		}
		newParent->part2 = newWindow;			// add newWindow to other side of parent

		// **** modify heap *************
		WindowNode& temp = *heap[index];
		heap[index] = heap[size];  // swap target and newParent
		heap[size] = &temp;

		// check for success
		success = contains(windowID);
		if (success) {
			size += 2; // record size change
		}
	}

	cout << endl;
	printSideways(root);
	cout << endl;
	printHeap(heap);
	cout << endl;

	if (success)
		numWindows++;
	if (!success)
		throw string("ERROR: fail to add WindowNode to WindowTree");

	return success;
}


/**
 * @brief removes a node with given WindowID
 *
 * @param windowID
 * @return true if node found and removed
 * @return false if node not found
 * throw string if node found but not removed
 */
bool WindowTree::remove(int targetID)
{
	std::cout << "WindowTree::remove" << endl;
	std::cout << "targetID: " << targetID << endl;

	if (size == 0)
	{
		return false;  // basic
	}

	bool success;

	if (size == 1)
	{
		delete root->part1;
		root->part1 = nullptr; // easy
	}
	else
	{
		WindowNode* target = nullptr;
		int targetIndex = (size - 1) / 2 ;  // starting here lets us skip parent nodes

		do	// get target node and index
		{
			target = heap[targetIndex];
			targetIndex++;
		}
		while (target->window->windowID != targetID && targetIndex < heap.size());
		targetIndex--;

		int parentIndex = (targetIndex - 1) / 2;
		int grandpaIndex = (parentIndex - 1) / 2;

		if (target->window->windowID != targetID)
			return false;  // target not found

		WindowNode* parentOfTarget = heap[parentIndex];
		bool isLeftChild = target == parentOfTarget->part1;
		bool isRightChild = target == parentOfTarget->part2;
		int survivorIndex; // this is the index of the sibling node that is not removed

		if (isLeftChild)
			survivorIndex = targetIndex + 1;
		if (isRightChild)
			survivorIndex = targetIndex - 1;

		if (size == 2 && isRightChild)
		{
			delete root->part2;  // simple
			root->part2 = nullptr;
			if(contains(targetID))
				throw string("ERROR: failure to remove WindowNode from WindowTree");
		}
		else if (size == 2 && isLeftChild)
		{
			delete root->part1;  // simple
			root->part1 = nullptr;
			if(contains(targetID))
				throw string("ERROR: failure to remove WindowNode from WindowTree");
		}
		else if (size == 2)
		{
			return false;  // target not found
		}

		// **** get other relevant nodes ***************
		WindowNode* leftTemp = parentOfTarget->part1;
		WindowNode* rightTemp = parentOfTarget->part2;
		WindowNode* grandpa = heap[grandpaIndex];

		bool isLeftGrandchild = grandpa->part1 == parentOfTarget;
		bool isRightGrandchild = grandpa->part2 == parentOfTarget;

		// **** remove parent and target node **********
		// **** clean up pointers and reorder tree ****
		if (isLeftChild && isLeftGrandchild)
		{
			grandpa->part1 = rightTemp;
			parentOfTarget->part1 = nullptr;
			delete target;
			delete parentOfTarget;
		}
		else if (isLeftChild && isRightGrandchild)
		{
			grandpa->part2 == rightTemp;
			parentOfTarget->part1 = nullptr;
			delete target;
			delete parentOfTarget;
		}
		else if (isRightChild && isLeftGrandchild)
		{
			grandpa->part1 == leftTemp;
			parentOfTarget->part2 = nullptr;
			delete target;
			delete parentOfTarget;
		}
		else if (isRightChild && isRightGrandchild)
		{
			grandpa->part2 == leftTemp;
			parentOfTarget->part2 = nullptr;
			delete target;
			delete parentOfTarget;
		}
		else
		{
			return false;
		}

		// **** modify heap ****
		WindowNode& temp = *heap[survivorIndex];  // swap surviving child with parent
		heap[survivorIndex] = heap[parentIndex];
		heap[parentIndex] = &temp;

		printHeap(heap);
		cout << endl;

		if (targetIndex > survivorIndex)
		{
			heap.erase(heap.begin() + targetIndex);	  // remove nodes from heap
			heap.erase(heap.begin() + survivorIndex);
		}
		else
		{
			heap.erase(heap.begin() + survivorIndex);
			heap.erase(heap.begin() + targetIndex);	  // remove nodes from heap
		}
	}

	// **** check for success/failure *********

/*
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

*/

	cout << endl;
	printSideways(root);
	cout << endl;
	printHeap(heap);
	cout << endl;

	success = !contains(targetID);
	if (success)
	{
		size--;
		numWindows--;
	}
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