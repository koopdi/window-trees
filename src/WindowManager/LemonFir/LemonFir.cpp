/**
 * @file LemonFir.cpp
 * @author Travis McKinney (movonarvic@gmail.com)
 * @brief This file contains method definitions for class LemonFir.
 * See LemonFir.h for a high level overview.
 * @version 0.1
 * @date 06-11-2022
 */


#include "LemonFir.h"
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;

#define margin 1;

LemonFir::LemonFir(ServerInterface* server)
    : server(server)
{
	screen = server->getScreens()[0];
}

void LemonFir::addWindow(long windowID)
{
	PanePtr newWindow = std::make_shared<Pane>(windowID);
	nextOpen()        = newWindow;
}

void LemonFir::remWindow(long windowID)
{
	remove(tree, windowID);
	std::vector<long> windows = server->getWindows(screen);
	for (long ID : windows) {
	}
}

void LemonFir::render(ServerInterface* server)
{

	Area size = server->getScreenSize(screen);

	render(tree, size);
}

void LemonFir::rotateSplit(long windowID)
{
	NodePtr* parent = getParent(windowID);

	if (Split* s = getSplit(parent)) {
		if (Pane* p = getPane(s->left)) {
		}
		if (Pane* p = getPane(s->right)) {
		}
		s->vSplit = !s->vSplit;
	}
}

void LemonFir::swapWindows(long windowA, long windowB)
{
	NodePtr* nodeA = getTreePane(windowA);
	NodePtr* nodeB = getTreePane(windowB);

	if (nodeA && nodeB) {
		Pane* paneA = getPane(nodeA);
		Pane* paneB = getPane(nodeB);
		if (paneA && paneB) {
			nodeA->swap(*nodeB);
		}
	}
}

void LemonFir::resize(Area area) {}

// Private Methods -----------------------------------------

void LemonFir::print()
{
	cout << "\t\t--------Printing Tree ---------" << endl;
	print(tree);
}

void LemonFir::print(NodePtr node)
{
	if (node) {
		std::cout << node->type << endl;
		if (Split* s = getSplit(node)) {
			print(s->left);
			print(s->right);
		} else if (Pane* p = getPane(node)) {
			cout << "ID: " << p->windowID << endl;
		}
	}
}

NodePtr& LemonFir::nextOpen()
{ // Begin search at the root.
	return nextOpen(tree);
}

NodePtr& LemonFir::nextOpen(NodePtr& node)
{              // Recursively search until a null node or a pane node is found.
	if (!node) { // Empty
		return node;

	} else if (Split* s = getSplit(node)) { // Split
		// attatch window here, or here, or here, or here....
		return nextOpen(s->right);

	} else if (Pane* p = getPane(node)) { // Pane
		// find the parent of the pane
		Split* parent     = getSplit(getParent(p->windowID));

		// move this pane into a new split
		NodePtr temp      = node;
		SplitPtr newSplit = std::make_shared<Split>();
		node              = newSplit;
		newSplit->left    = temp;

		// Set the split direction opposite the parent.
		if (parent) {
			newSplit->vSplit = !parent->vSplit;
		}

		// Return the open spot in the new split.
		return newSplit->right;
	}
}

void LemonFir::render(NodePtr node, Area& space)
{
	if (node) {
		if (Split* s = getSplit(node)) {
			if (s->vSplit) {
				space.width = (space.width * 0.5) - margin;
			} else {
				space.height = (space.height * 0.5) - margin;
			}
			render(s->left, space);
			if (s->vSplit) {
				space.x += space.width + 2 * margin;
			} else {
				space.y += space.height + 2 * margin;
			}
			render(s->right, space);
		} else if (Pane* p = getPane(node)) {
			server->setArea(p->windowID, space);
		}
	}
}

void LemonFir::remove(NodePtr& node, long targetID)
{
	if (Pane* p = getPane(node)) {
		if (p->windowID == targetID) {
			node = nullptr;
		}
	}
	if (Split* s = getSplit(node)) {
		// look ahead left
		if (Pane* p = getPane(s->left)) {
			if (p->windowID == targetID) {
				// remove left
				s->left = nullptr;
				// link this node's parent to the right
				node    = s->right;
			}
		}
		// look ahead right
		if (Pane* p = getPane(s->right)) {
			if (p->windowID == targetID) {
				// remove right
				s->right = nullptr;
				// link this node's parent to the left
				node     = s->left;
			}
		} // recurse
		remove(s->left, targetID);
		remove(s->right, targetID);
	}
}

NodePtr* LemonFir::getParent(long targetID)
{
	return getParent(&tree, targetID);
}

NodePtr* LemonFir::getParent(NodePtr* node, long targetID)
{
	if (Split* s = getSplit(node)) {
		// look ahead left
		if (Pane* p = getPane(s->left)) {
			if (p->windowID == targetID) {
				return node;
			}
		}
		// look ahead right
		if (Pane* p = getPane(s->right)) {
			if (p->windowID == targetID) {
				return node;
			}
		}
		// recurse
		NodePtr* left = getParent(&s->left, targetID);
		if (left) {
			return left;
		} else {
			return getParent(&s->right, targetID);
		}
	} else {
		return nullptr;
	}
}

NodePtr* LemonFir::getTreePane(long targetID)
{
	return getTreePane(&tree, targetID);
}

NodePtr* LemonFir::getTreePane(NodePtr* node, long targetID)
{
	if (!node) {
		return nullptr;
	}

	if (Pane* p = getPane(node)) {
		if (p->windowID == targetID) {
			return node;
		} else {
			return nullptr;
		}
	}

	if (Split* s = getSplit(node)) {
		NodePtr* left = getTreePane(&s->left, targetID);
		if (left) {
			return left;
		} else {
			return getTreePane(&s->right, targetID);
		}
	}

	return nullptr;
}