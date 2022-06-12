#include "HeapTree.h"

#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

// not implemented
void HeapTree::swapWindows(long windowA, long windowB){ /*do nothing*/ }


// not implemented
void HeapTree::rotateSplit(long windowID) { /*do nothing*/ }

/**
 * @brief Construct a new Heap Tree:: Heap Tree object
 *
 */
HeapTree::HeapTree() {
	cout << "HEAP TREE constructor" << endl;

	last = nullptr;
	heap.push_back(new HeapWindow());
	root = heap[0]->node;
	heap[0]->area = area;
	size = 1;
	numWindows = 0;
}

/**
 * @brief Construct a new Heap Tree:: Heap Tree object
 *
 * @param server the abstract interface
 */
HeapTree::HeapTree(ServerInterface* server): HeapTree() {
	this->server = server;
}

/**
 * @brief add a window to the tree
 *
 * @param windowID the ID for the window
 */
void HeapTree::addWindow(long windowID) { add(windowID);}

/**
 * @brief remove a window from the tree
 *
 * @param windowID the ID for the window
 */
void HeapTree::remWindow(long windowID) { remove(windowID); }

/**
 * @brief resize a window
 *
 * @param area the area of the window
 */
void HeapTree::resize(Area area) { this->area = area; }

/**
 * @brief render all the windows
 *
 * @param server the abstract interface
 */
void HeapTree::render(ServerInterface* server) {
	for (const HeapWindow* window: heap)
	{
		server->setArea(window->node->window.windowID, window->area);
	}
}

/**
 * @brief  add a window to the tree
 *
 * It adds a new window to the heap tree. If the size of the heap tree is less than 2, it simply
 * adds the new window to the end of the heap. If the size of the heap tree is 2 or more, it adds
 * the new window as a child of the parent of the target window, and makes the target window the
 * child of the new parent. It then swaps the target window and the new window in the heap.
 *
 * @param windowID an ID for a window
 * @return true // add successful
 * @return false // add failed
 */
bool HeapTree::add(int windowID) // TODO: change part1Size when moving nodes
{
	std::cout << "WindowTree::add" << endl;
	bool success = false;

	if (size <= 2)
	{
		heap.push_back(new HeapWindow(windowID));
		if (size == 1)
		{
			heap[0]->node->part1 = heap.back()->node; // add left node
		}
		else
		{
			heap[0]->node->part2 = heap.back()->node;
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
		HeapWindow* target = heap[(size - 1) / 2];
		// having the parent makes reassigning nodes easier
		HeapWindow* parentOfTarget = heap[(index - 1) / 2];

		// one of these will be target
		WindowNode* leftChild = parentOfTarget->node->part1;  // child of parentOfTarget
		WindowNode* rightChild = parentOfTarget->node->part2; // child of parentOfTarget

		// each add after node 2 requires 2 nodes, a parent and window
		HeapWindow* newParent = new HeapWindow();
		HeapWindow* newWindow = new HeapWindow(windowID, workspaceID);
		heap.push_back(newParent);		// add new nodes to heap
		heap.push_back(newWindow);

		// **** modify tree ***************
		if (leftChild == target->node)  // check which child is our target for building from
		{
			newParent->node->part1 = leftChild;  			// swap target with newParent
			parentOfTarget->node->part1 = newParent->node;
		}
		else
		{
			newParent->node->part1 = rightChild;			// swap target with newParent
			parentOfTarget->node->part2 = newParent->node;
		}
		newParent->node->part2 = newWindow->node;			// add newWindow to other side of parent

		// **** modify heap *************
		HeapWindow*& temp = heap[index];
		heap[index] = heap[size];  // swap target and newParent
		heap[size] = temp;

		// check for success
		success = contains(windowID);
		if (success) {
			size += 2; // record size change
		}
	}

	if (success)
		numWindows++;
	if (!success)
		throw string("ERROR: fail to add WindowNode to WindowTree");

	return success;
}

int HeapTree::getSize() const { return size; }

bool HeapTree::isEmpty() const { return numWindows == 0; }

int HeapTree::getNumWindows() const { return numWindows; }

void HeapTree::printSideways(WindowNode* root) const { printSidewaysHelper(root, ""); }

void HeapTree::printSidewaysHelper(WindowNode* root, string spaces)  const{
    if(root != nullptr) {
        printSidewaysHelper(root->part2, spaces + "    ");
        cout << spaces << (root->isWindow() ? root->window.windowID : (size_t)root) << endl;
        printSidewaysHelper(root->part1, spaces + "    ");
    }
}

bool HeapTree::contains(int targetID) const
{
	int index = (size - 1) / 2;  // starting here lets us skip parent nodes

	for (;index < heap.size(); index++)
	{
		int foundID = heap[index]->node->window.windowID;
		if (foundID == targetID)
			return true;
	}

	return false;
}

bool HeapTree::contains(WindowNode* target) const
{
	for (const HeapWindow* window: heap){
		if (window->node == target)
			return true;
	}
	return false;
}

void HeapTree::printHeap(const std::vector<HeapWindow*>& heap) const {
	int num = 0;
	for (HeapWindow* window: heap) {
		cout << num << ": " << "area: " << window->area.width << "x" << window->area.height;
		num++;
		cout << (window->node->isWindow() ? window->node->window.windowID : (long long)window->node) << endl;
	}
}

/**
 * @brief removes a node with given WindowID
 *
 * @param windowID
 * @return true if node found and removed
 * @return false if node not found
 * throw string if node found but not removed
 */
bool HeapTree::remove(int targetID)
{
	std::cout << "WindowTree::remove" << endl;

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
		// **** get target node and index ***************
		HeapWindow* target;
		int index = (size - 1) / 2 ;  // starting here lets us skip parent nodes

		do
		{
			target = heap[index];
			index++;
		}
		while (target->node->window.windowID != targetID && index < heap.size());
		index--;

		if (target->node->window.windowID != targetID)
			return false;  // target not found

		HeapWindow* parentOfTarget = heap[(index - 1) / 2];
		bool isLeftChild = target->node == parentOfTarget->node->part1;
		bool isRightChild = target->node == parentOfTarget->node->part2;

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
		WindowNode* leftTemp = parentOfTarget->node->part1;
		WindowNode* rightTemp = parentOfTarget->node->part2;
		HeapWindow* grandpa = heap[((index - 1) / 2 - 1) / 2];

		bool isLeftGrandchild = grandpa->node->part1 == parentOfTarget->node;
		bool isRightGrandchild = grandpa->node->part2 == parentOfTarget->node;

		// **** clean up pointers and reorder tree ****
		if (isLeftChild && isLeftGrandchild)
		{
			parentOfTarget->node->part1 = nullptr;
			grandpa->node->part1 = leftTemp;
		}
		else if (isLeftChild && isRightGrandchild)
		{
			parentOfTarget->node->part1 = nullptr;
			grandpa->node->part2 == leftTemp;
		}
		else if (isRightChild && isLeftGrandchild)
		{
			parentOfTarget->node->part2 = nullptr;
			grandpa->node->part1 == rightTemp;
		}
		else if (isRightChild && isRightGrandchild)
		{
			parentOfTarget->node->part2 = nullptr;
			grandpa->node->part2 == rightTemp;
		}
	}

	// **** check for success/failure *********

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

// void HeapTree::preOrderTraverse(WindowNode* node, forEachNode func) const
// {
// 	if (node == nullptr) return;
// 	// run the function and save result
// 	bool keepGoing = func(node);
// 	if (keepGoing)
// 	{
// 		// recurse
// 		preOrderTraverse(node->part1, func);
// 		preOrderTraverse(node->part2, func);
// 	}
// }

// void HeapTree::inOrderTraverse(WindowNode* node,
//                                  std::function<bool(WindowNode*)> func) const
// {
// 	if (node == nullptr) return;

// 	inOrderTraverse(node->part1, func);
// 	bool keepGoing = func(node);
// 	if (keepGoing)
// 	{
// 		inOrderTraverse(node->part2, func);
// 	}
// }

// void HeapTree::postOrderTraverse(WindowNode* node, forEachNode func) const
// {
// 	if (node == nullptr) return;

// 	postOrderTraverse(node->part1, func);
// 	postOrderTraverse(node->part2, func);
// 	func(node);
// }