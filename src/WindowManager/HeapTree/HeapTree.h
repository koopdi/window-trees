#pragma once

#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

#include "ServerInterface.h"
#include "WindowTreeInterface.h"
#include "WindowNode.h"
#include "types.h"

class Workspace;

class HeapTree : public WindowTreeInterface
{
public:
	HeapTree();
	void render(ServerInterface* server) override;
	void addWindow(long windowID) override;
	void remWindow(long windowID) override;
	void resize(Area area) override;
	void rotateSplit(long windowID);
	/// Switch the positions of A and B.
	void swapWindows(long windowA, long windowB) override;

	void update();

	HeapTree(ServerInterface* server);

private:
	Area area;						// the area of the workspace the tree's windows are on
	int numWindows;  				// the number of windows
	int workspaceID;				// the ID for the Workspace that owns the tree
	int size;  						// the size of the tree
	HeapWindow* root;   			// a pointer to the root node of the tree
	HeapWindow* last; 				// a pointer to the most recently added node
	std::vector<HeapWindow*> heap;	// a heap of Windows with WindowNodes that is in sync with the tree
	std::stack<int> removed; 		// indexes of removed parent HeapWindows
	ServerInterface* server;

	// bool isEmpty() const;
	bool contains(int windowID) const;
	bool contains(HeapWindow* node) const;
	// int getSize() const;
	// int getNumWindows() const;
	void printHeap(const std::vector<HeapWindow*>& heap) const;
	// WindowNode* get(int windowID) const;
	// WindowNode* getRoot() const;
	void printSideways(HeapWindow* root) const;
	void printSidewaysHelper(HeapWindow* root, std::string spaces) const;
	// int getIndex(WindowNode* node) const;
	// WindowNode* getParent(WindowNode*) const;
	// //void preOrderTraverse(WindowNode* node, forEachNode func) const;
	// WindowNode*& getRef(int windowID) const;
	// //void inOrderTraverse(WindowNode* node, forEachNode func) const;
	// //void postOrderTraverse(WindowNode* node, forEachNode func) const;
	// WindowNode*& getByIndex(int index) const;
	bool add(int windowID);
	// //add(int windowID, windowNode* node);
	// void addHelper(int& index, WindowNode*& target, WindowNode*& parentOfTarget);
	bool remove(int windowID);
	// bool remove(WindowNode*& node);
	// void QueueTree(WindowNode* root, std::queue<WindowNode*>& levelOrder);
	// //queueLevel(WindowNode* node, int level, std::queue<WindowNode*>& levelOrder);
	// //void breadthFirstSearch(WindowNode* node, forEachNode func);
	// int calculateHeight(WindowNode* node, int windowID, double height);
	// int height(WindowNode* node);
	// void clear();
	// //~HeapTree();

	/// A function that is passed to a xyzTraverse function.
	// using forEachNode = std::function<bool(WindowNode*)>;
};