#include "HeapTree.h"

#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

void HeapTree::swapWindows(long windowA, long windowB)
{
	/*do nothing*/
}

void HeapTree::rotateSplit(long windowID)
{
	 /*do nothing*/
}

HeapTree::HeapTree():
	area ({0,0,0,0}),			// the area of the workspace the tree's windows are on
	numWindows(0),  			// the number of windows
	workspaceID(0),				// the ID for the Workspace that owns the tree
	size(0), 					// the size of the tree
	root(0),   					// a pointer to the root node of the tree
	last(0), 					// a pointer to the most recently added node
	heap(vector<HeapWindow*>()),// a heap of Windows with WindowNodes that is in sync with the tree
	removed(stack<int>())		// indexes of removed parent HeapWindows
 {
	cout << "HEAP TREE constructor" << endl;
	root = new HeapWindow(0, 50, 0, 0);
	heap.push_back(root);
	size = 1;
}

HeapTree::HeapTree(ServerInterface* server): HeapTree()
{
	this->server = server;
	auto screens = server->getScreens();
	int screenID = *(screens.begin()); // get ID from screen #1

	area = server->getScreenSize(screenID);
	cout << "area: " << area.width << "x" << area.height <<endl;
	cout << "x: " << area.x << " y: " << area.y << endl;
}


void HeapTree::addWindow(long windowID) { add(windowID); }
void HeapTree::remWindow(long windowID) { remove(windowID); }
void HeapTree::resize(Area area) { this->area = area; }
void HeapTree::render(ServerInterface* server) {
	cout << "HeapTree render" << endl;
	for (const HeapWindow* window: heap)
	{
		if(window->isWindow())
		{
			server->setArea(window->windowID, window->area);
			cout << "ID: " << window->windowID << " area: " << window->area.width << "x" << window->area.height << endl;
		}
	}
}

bool HeapTree::add(int windowID)
{
	std::cout << "WindowTree::add" << endl;
	bool success = false;
	cout << "size: " << size << endl;

	if (!removed.empty())
	{
		// get the HeapWindow at the locations of the most recently removed HeapWindow
		int index = removed.top();
		HeapWindow* target = heap[index];

		// get the parent of the target
		HeapWindow* targetParent = heap[index - 1 / 2];

		// determine if target is a left or right child
		bool isLeftChild = targetParent->left = target;
		bool isRightChild = targetParent->right = target;

		// partVertically alternates
		bool partVertically = !targetParent->partVertically;

		// determine part1Size
		int part1Size = 50; // TODO: allow different values

		// push new window node
		heap.push_back(new HeapWindow(windowID, area));

		// create new parent node
		HeapWindow* newParent = new HeapWindow(partVertically, part1Size, target, heap.back());

		// init values for area
		int width = target->area.width;
		int height = target->area.height;
		int remainder;

		// set left child area
		if (targetParent->partVertically)
		{
			height = height / 2;
			remainder = height % 2;
			target->area.height = height + remainder;
		}
		else
		{
			width = width / 2;
			remainder = width % 2;
			target->area.width = width + remainder;
		}

		// set right child area
		if (targetParent->partVertically)
		{
			newParent->right->area = Area {target->area.x, target->area.height, width, height};
		}
		else
		{
			newParent->right->area = Area {target->area.width, target->area.y, width, height};
		}

		// add new parent
		if (isLeftChild)
			targetParent->left = newParent;
		if (isRightChild)
			targetParent->right = newParent;

		success = contains(windowID);

		if (success)
		{
			size += 2;
			numWindows++;
			removed.pop();
		}
	}
	else if (size == 1)
	{
		root->area = area;  // set area for first node

		// add first window
		heap.push_back(new HeapWindow(windowID, area));
		root->left = heap.back();

//		root->left->part1Size = 50;
//		root->left->partVertically = !root->partVertically;

		// check for success
		success = contains(windowID);

		if (success)
		{
			size++;
			numWindows++;
		}
		else
			throw string("failed to add first window");
	}
	else if (size == 2)
	{
		if (root->right != nullptr)  // move to left
			root->left = root->right;

		// set first window area to half
		int width = root->area.width * root->part1Size / 100;
		root->left->area = Area{0, 0, width, root->area.height};

		// set area for new window
		width = root->area.width * (100 - root->part1Size) / 100;
		Area newArea = Area{width, 0, width, root->area.height};

		// add new window
		heap.push_back(new HeapWindow(windowID, newArea));
		root->right = heap.back();

//		root->right->part1Size = 50;
//		root->right->partVertically = !root->partVertically;

		// check for success
		success = contains(windowID);

		if (success)
		{
			size++;
			numWindows++;
		}
		else
			throw string("failed to add second window");
	}
	else
	{
		int index = (size - 1) /2;
		// target is the node that will be built off of
		HeapWindow* target = heap[(size - 1) / 2];
		// having the parent makes reassigning nodes easier
		HeapWindow* parentOfTarget = heap[(index - 1) / 2];

		// one of these will be target
		HeapWindow* leftChild = parentOfTarget->left;  // child of parentOfTarget
		HeapWindow* rightChild = parentOfTarget->right; // child of parentOfTarget

		// nodes always part the opposite of their parents
		bool partVertically = !(parentOfTarget->partVertically);

		// determine part1Size
		int part1Size = 50; // TODO: allow different values

		// init values for area
		const int width = target->area.width;
		const int height = target->area.height;

		// set left child area
		if (partVertically)
		{
			target->area.height = height * part1Size / 100;
		}
		else
		{
			target->area.width = width * part1Size / 100;
		}

		cout << endl;
		printSideways(root);
		cout << endl;
		printHeap(heap);
		cout << endl;

		Area newArea = Area{target->area.x, target->area.y, width, height};

		if (partVertically)
		{
			newArea.height = height * (100 - part1Size) / 100;
		}
		else
		{
			newArea.width =  width * (100 - part1Size) / 100;
		}

		if (partVertically)
		{
			newArea.x = target->area.x;
			newArea.y = target->area.y + target->area.height;
		}
		else
		{
			newArea.x = target->area.x + target->area.width;
			newArea.y = target->area.y;
		}

		// each add after node 2 requires 2 nodes, a parent and window
		HeapWindow* newWindow = new HeapWindow(windowID, newArea);
		HeapWindow* newParent = new HeapWindow(partVertically, part1Size, target, newWindow);
		heap.push_back(newParent);		// add new nodes to heap
		heap.push_back(newWindow);

		// cout << "target: " << target->window->windowID << endl;
		// cout << "parentOfTarget: " << parentOfTarget->window->windowID << endl;
		// cout << "tempLeft: " << leftChild->window->windowID << endl;
		// cout << "tempRight: " << rightChild->window->windowID << endl;
		// cout << "newParent: " << newParent->window->windowID << endl;
		// cout << " newWindow: " <<  newWindow->window->windowID << endl;

		cout << endl;
		printSideways(root);
		cout << endl;
		printHeap(heap);
		cout << endl;

		// **** modify tree ***************
		if (leftChild == target)  // check which child is our target for building from
		{
			parentOfTarget->left = newParent;
		}
		else
		{
			parentOfTarget->right = newParent;
		}

		cout << endl;
		printSideways(root);
		cout << endl;
		printHeap(heap);
		cout << endl;

		swap(heap[index], heap[size]);

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

	area = server->getScreenSize(99);
	cout << "area: " << area.width << "x" << area.height <<endl;
	cout << "x: " << area.x << " y: " << area.y << endl;

	area = server->getScreenSize(143);
	cout << "area: " << area.width << "x" << area.height <<endl;
	cout << "x: " << area.x << " y: " << area.y << endl;

	if (success)
		numWindows++;
	if (!success)
		throw string("ERROR: fail to add WindowNode to WindowTree");

	return success;
}




//HeapTree::~WindowTree() { clear(); }

// int HeapTree::getSize() const { return size; }

// bool HeapTree::isEmpty() const { return numWindows == 0; }

// int HeapTree::getNumWindows() const { return numWindows; }

//WindowNode* HeapTree::getRoot() { return root; }

void HeapTree::printSideways(HeapWindow* root) const { printSidewaysHelper(root, ""); }

void HeapTree::printSidewaysHelper(HeapWindow* root, string spaces)  const{
    if(root != nullptr) {
        printSidewaysHelper(root->right, spaces + "    ");
        cout << spaces << root->windowID << endl;
        printSidewaysHelper(root->left, spaces + "    ");
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
		int foundID = heap[index]->windowID;
		if (foundID == targetID)
			return true;
	}

	return false;
}

bool HeapTree::contains(HeapWindow* target) const
{
	for (const HeapWindow* window: heap){
		if (window == target)
			return true;
	}
	return false;

	// auto it = find(heap.begin(), heap.end(), target);
	// return *it == target;
}

void HeapTree::printHeap(const std::vector<HeapWindow*>& heap) const {
	int num = 0;
	for (HeapWindow* window: heap) {
		cout << num << ": " << "area: " << window->area.width << "x" << window->area.height;
		num++;
		cout << " ID: " << window->windowID << endl;
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
		delete root->left;
		root->left = nullptr; // easy
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
		while (target->windowID != targetID && index < heap.size());
		index--;

		if (target->windowID != targetID)
			return false;  // target not found

		HeapWindow* parentOfTarget = heap[(index - 1) / 2];
		bool isLeftChild = target == parentOfTarget->left;
		bool isRightChild = target == parentOfTarget->right;

		if (size < 4 && isRightChild)
		{
			delete root->right;  // simple
			root->right = nullptr;
			heap.erase(heap.begin() + 2);
			heap[1]->area = area;
			if(contains(targetID))
				throw string("ERROR: failure to remove WindowNode from WindowTree");
		}
		else if (size < 4 && isLeftChild)
		{
			delete root->left;  // simple
			root->left = nullptr;
			heap.erase(heap.begin() + 1);
			heap[2]->area = area;
			if(contains(targetID))
				throw string("ERROR: failure to remove WindowNode from WindowTree");
		}
		else if (size == 2)
		{
			return false;  // target not found
		}

		// **** get other relevant nodes ***************
		HeapWindow* leftTemp = parentOfTarget->left;
		HeapWindow* rightTemp = parentOfTarget->right;
		HeapWindow* grandpa = heap[((index - 1) / 2 - 1) / 2];

		bool isLeftGrandchild = grandpa->left == parentOfTarget;
		bool isRightGrandchild = grandpa->right == parentOfTarget;

		// **** clean up pointers and reorder tree ****
		if (isLeftChild && isLeftGrandchild)
		{
			parentOfTarget->left = nullptr;
			grandpa->right = leftTemp;
		}
		else if (isLeftChild && isRightGrandchild)
		{
			parentOfTarget->left = nullptr;
			grandpa->right == leftTemp;
		}
		else if (isRightChild && isLeftGrandchild)
		{
			parentOfTarget->right = nullptr;
			grandpa->left == rightTemp;
		}
		else if (isRightChild && isRightGrandchild)
		{
			parentOfTarget->right = nullptr;
			grandpa->right == rightTemp;
		}


		cout << size << endl;


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