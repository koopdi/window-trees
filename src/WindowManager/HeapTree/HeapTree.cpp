#include "HeapTree.h"

#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

void HeapTree::rotateSplit(long windowID) { /*do nothing*/ }

HeapTree::HeapTree() {
	last = nullptr;
	heap.push_back(Window());
	root = heap[0].node;
	size = 1;
	numWindows = 0;
}

HeapTree::HeapTree(ServerInterface* server) {
	HeapTree();
}


void HeapTree::addWindow(long windowID) { add(windowID);}
void HeapTree::remWindow(long windowID) { remove(windowID); }
void HeapTree::resize(Area area) { this->area = area; }
void HeapTree::render(ServerInterface* server) {
	for (Window window: heap)
	{
		server->setArea(window.node->window.windowID, window.area);
	}
}

bool HeapTree::add(int windowID) // TODO: change part1Size when moving nodes
{
	std::cout << "WindowTree::add" << endl;
	bool success = false;

	if (size <= 2)
	{
		heap.push_back(Window(windowID));
		if (size == 1)
		{
			heap[0].node->part1 = heap.back().node; // add left node
		}
		else
		{
			heap[0].node->part2 = heap.back().node;
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
		Window target = heap[(size - 1) / 2];
		// having the parent makes reassigning nodes easier
		Window parentOfTarget = heap[(index - 1) / 2];

		// one of these will be target
		WindowNode* leftChild = parentOfTarget.node->part1;  // child of parentOfTarget
		WindowNode* rightChild = parentOfTarget.node->part2; // child of parentOfTarget

		// nodes always part the opposite of their parents
		//bool partVertically = !(target->partVertically);

		// each add after node 2 requires 2 nodes, a parent and window
		Window newParent = Window();
		Window newWindow = Window(windowID, workspaceID);
		heap.push_back(newParent);		// add new nodes to heap
		heap.push_back(newWindow);

		// cout << "target: " << target->window->windowID << endl;
		// cout << "parentOfTarget: " << parentOfTarget->window->windowID << endl;
		// cout << "tempLeft: " << leftChild->window->windowID << endl;
		// cout << "tempRight: " << rightChild->window->windowID << endl;
		// cout << "newParent: " << newParent->window->windowID << endl;
		// cout << " newWindow: " <<  newWindow->window->windowID << endl;

		// **** modify tree ***************
		if (leftChild == target.node)  // check which child is our target for building from
		{
			newParent.node->part1 = leftChild;  			// swap target with newParent
			parentOfTarget.node->part1 = newParent.node;
		}
		else
		{
			newParent.node->part1 = rightChild;			// swap target with newParent
			parentOfTarget.node->part2 = newParent.node;
		}
		newParent.node->part2 = newWindow.node;			// add newWindow to other side of parent

		// **** modify heap *************
		Window& temp = heap[index];
		heap[index] = heap[size];  // swap target and newParent
		heap[size] = temp;

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




//HeapTree::~WindowTree() { clear(); }

int HeapTree::getSize() const { return size; }

bool HeapTree::isEmpty() const { return numWindows == 0; }

int HeapTree::getNumWindows() const { return numWindows; }

//WindowNode* HeapTree::getRoot() { return root; }

void HeapTree::printSideways(WindowNode* root) const { printSidewaysHelper(root, ""); }

void HeapTree::printSidewaysHelper(WindowNode* root, string spaces)  const{
    if(root != nullptr) {
        printSidewaysHelper(root->part2, spaces + "    ");
        cout << spaces << (root->isWindow() ? root->window.windowID : (size_t)root) << endl;
        printSidewaysHelper(root->part1, spaces + "    ");
    }
}

// WindowNode* HeapTree::get(int targetID)
// {
// 	int index = (size - 1) / 2;  // starting here lets us skip parent nodes

// 	for (;index < heap.size(); index++)
// 	{
// 		WindowNode* node = heap[index];
// 		if (node->window->windowID == targetID)
// 			return node;
// 	}

// 	return nullptr;
// }

bool HeapTree::contains(int targetID) const
{
	int index = (size - 1) / 2;  // starting here lets us skip parent nodes

	for (;index < heap.size(); index++)
	{
		int foundID = heap[index].node->window.windowID;
		if (foundID == targetID)
			return true;
	}

	return false;
}

bool HeapTree::contains(WindowNode* target) const
{
	for (Window window: heap){
		if (window.node == target)
			return true;
	}
	return false;

	// auto it = find(heap.begin(), heap.end(), target);
	// return *it == target;
}

void HeapTree::printHeap(vector<Window> heap) const {
	int num = 0;
	for (Window window: heap) {
		cout << num << ": ";
		num++;
		cout << (window.node->isWindow() ? window.node->window.windowID : (long long)window.node) << endl;
	}
}

// void HeapTree::addHelper(int& index, WindowNode*& target, WindowNode*& parentOfTarget)
// {
// 	index = 1;
// 	parentOfTarget = heap[0];
// 	target = heap[1];
// 	WindowNode* next = heap[1];

// 	while (next->window->windowID == -1)
// 	{
// 		parentOfTarget = heap[index - 1];
// 		target = heap[index];
// 		next = heap[index + 1];
// 		index++;
// 	}

// 	cout << "index: " << index << endl;
// }

// bool HeapTree::add(double part1Size, int windowID) // TODO: change part1Size when moving nodes
// {
// 	std::cout << "WindowTree::add" << endl;
// 	bool success = false;

// 	if (size <= 2)
// 	{
// 		heap.push_back(new WindowNode(1, windowID, workspaceID));
// 		if (size == 1)
// 		{
// 			root->part1Size = 1.;
// 			root->part1 = heap.back();
// 		}
// 		else
// 		{
// 			root->part1Size = part1Size;
// 			root->part2 = heap.back();
// 		}
// 		success = contains(windowID);

// 		if (success)
// 			size++;
// 		if (!success)
// 			throw string("failed to add early node");
// 	}
// 	else
// 	{
// 		int index = (size - 1) /2;
// 		// target is the node that will be built off of
// 		WindowNode* target = heap[(size - 1) / 2];
// 		// having the parent makes reassigning nodes easier
// 		WindowNode* parentOfTarget = heap[(index - 1) / 2];

// 		// one of these will be target
// 		WindowNode* leftChild = parentOfTarget->part1;  // child of parentOfTarget
// 		WindowNode* rightChild = parentOfTarget->part2; // child of parentOfTarget

// 		// nodes always part the opposite of their parents
// 		bool partVertically = !(target->partVertically);

// 		// each add after node 2 requires 2 nodes, a parent and window
// 		WindowNode* newParent = new WindowNode(partVertically);
// 		WindowNode* newWindow = new WindowNode(partVertically, windowID, workspaceID);

// 		newParent->part1Size = part1Size;		// set part1size

// 		heap.push_back(newParent);		// add new nodes to heap
// 		heap.push_back(newWindow);

// 		// cout << "target: " << target->window->windowID << endl;
// 		// cout << "parentOfTarget: " << parentOfTarget->window->windowID << endl;
// 		// cout << "tempLeft: " << leftChild->window->windowID << endl;
// 		// cout << "tempRight: " << rightChild->window->windowID << endl;
// 		// cout << "newParent: " << newParent->window->windowID << endl;
// 		// cout << " newWindow: " <<  newWindow->window->windowID << endl;

// 		// **** modify tree ***************
// 		if (leftChild == target)  // check which child is our target for building from
// 		{
// 			newParent->part1 = leftChild;  			// swap target with newParent
// 			parentOfTarget->part1 = newParent;
// 		}
// 		else
// 		{
// 			newParent->part1 = rightChild;			// swap target with newParent
// 			parentOfTarget->part2 = newParent;
// 		}
// 		newParent->part2 = newWindow;			// add newWindow to other side of parent

// 		// **** modify heap *************
// 		WindowNode& temp = *heap[index];
// 		heap[index] = heap[size];  // swap target and newParent
// 		heap[size] = &temp;

// 		// check for success
// 		success = contains(windowID);
// 		if (success) {
// 			size += 2; // record size change
// 		}
// 	}

// 	cout << endl;
// 	printSideways(root);
// 	cout << endl;
// 	printHeap(heap);
// 	cout << endl;

// 	if (success)
// 		numWindows++;
// 	if (!success)
// 		throw string("ERROR: fail to add WindowNode to WindowTree");

// 	return success;
// }


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
		Window target;
		int index = (size - 1) / 2 ;  // starting here lets us skip parent nodes

		do
		{
			target = heap[index];
			index++;
		}
		while (target.node->window.windowID != targetID && index < heap.size());
		index--;

		if (target.node->window.windowID != targetID)
			return false;  // target not found

		Window parentOfTarget = heap[(index - 1) / 2];
		bool isLeftChild = target.node == parentOfTarget.node->part1;
		bool isRightChild = target.node == parentOfTarget.node->part2;

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
		WindowNode* leftTemp = parentOfTarget.node->part1;
		WindowNode* rightTemp = parentOfTarget.node->part2;
		Window grandpa = heap[((index - 1) / 2 - 1) / 2];

		bool isLeftGrandchild = grandpa.node->part1 == parentOfTarget.node;
		bool isRightGrandchild = grandpa.node->part2 == parentOfTarget.node;

		// **** remove parent and target node **********

		if (isLeftChild || isRightChild)
		{
			// delete target;
			// delete parentOfTarget;
		}
		else
		{
			return false;  // target not found
		}

		// **** clean up pointers and reorder tree ****
		if (isLeftChild && isLeftGrandchild)
		{
			parentOfTarget.node->part1 = nullptr;
			grandpa.node->part1 = leftTemp;
		}
		else if (isLeftChild && isRightGrandchild)
		{
			parentOfTarget.node->part1 = nullptr;
			grandpa.node->part2 == leftTemp;
		}
		else if (isRightChild && isLeftGrandchild)
		{
			parentOfTarget.node->part2 = nullptr;
			grandpa.node->part1 == rightTemp;
		}
		else if (isRightChild && isRightGrandchild)
		{
			parentOfTarget.node->part2 = nullptr;
			grandpa.node->part2 == rightTemp;
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

// void HeapTree::clear()
// {
// 	forEachNode func = [this](WindowNode* node) -> bool { delete node; return true;};
// 	postOrderTraverse(root, func);
// }

// void HeapTree::breadthFirstSearch(WindowNode* node,
//                                     std::function<bool(WindowNode*)> func)
// {
// 	queue<WindowNode*> levelOrder;
// 	QueueTree(root, levelOrder);

// 	while (!levelOrder.empty())
// 	{
// 		WindowNode* node = levelOrder.front();
// 		func(node);
// 		levelOrder.pop();
// 	}
// }

// int HeapTree::height(WindowNode* node)
// {
// 	if (node == nullptr) return 0;

// 	int left  = height(node->part1);
// 	int right = height(node->part2);

// 	if (left > right)
// 	{
// 		return (left + 1);
// 	}
// 	else
// 	{
// 		return (right + 1);
// 	}
// }

// void HeapTree::QueueTree(WindowNode* root, queue<WindowNode*>& levelOrder)
// {
// 	int treeHeight = height(root);
// 	for (int i = 1; i <= treeHeight; i++)
// 	{
// 		queueLevel(root, i, levelOrder);
// 	}
// }

// void HeapTree::queueLevel(WindowNode* node,
//                             int level,
//                             queue<WindowNode*>& levelOrder)
// {
// 	if (node == nullptr) return;
// 	if (level == 1) levelOrder.push(node);
// 	else if (level > 1)
// 	{
// 		queueLevel(node->part1, level - 1, levelOrder);
// 		queueLevel(node->part2, level - 1, levelOrder);
// 	}
// }

// work in progress ******************************

// int HeapTree::calculateHeight(WindowNode* node, int windowID, double height)
// {
// 	// TODO: fix this

// 	if (node == nullptr) return 0;
// 	if (node->isWindow() && (node->window->windowID == windowID))
// 	{
// 		return height;
// 	}
// 	else if (node->partVertically)
// 	{
// 		calculateHeight(node->part1, windowID, (height * node->part1Size));
// 		calculateHeight(node->part2, windowID, (height * (100. - node->part1Size)));
// 	}
// 	else
// 	{
// 		calculateHeight(node->part1, windowID, height);
// 		calculateHeight(node->part2, windowID, height);
// 	}
// 	return 0;
// }

// work in progress ******************************