/**
 * @file Workspace.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */

#include "Workspace.h"

#include <iostream>
#include <string>

Workspace::Workspace(ServerInterface* server, WindowTreeInterface* mtree)
    : workspaceID((long long)(this)), server(server), tree(nullptr),
      metaTree(mtree)
{
	if(metaTree == nullptr)
	{
		tree = new WindowTree(this);
	}
}

bool Workspace::operator<(Workspace& other)
{
	return workspaceID < other.workspaceID;
}

bool operator<(std::shared_ptr<Workspace>& a, std::shared_ptr<Workspace>& b)
{
	return (*a) < (*b);
}

int Workspace::getHeight() const { return height; }

int Workspace::getWidth() const { return width; }

Point Workspace::getPosition() const { return position; }

int Workspace::getNumWindows() const { return numWindows; }

void Workspace::setHeight(int height) { this->height = height; }

void Workspace::setWidth(int width) { this->width = width; }

void Workspace::setPosition(Point position) { this->position = position; }

bool Workspace::addWindow(int windowID, double part1Size)
{
	using namespace std;
	cout << "In method workspace::addWindow." << endl;
	if (tree == nullptr) {
		cout << "tree is null" << endl;
		throw "Workspace: cannot add to null tree"s;
	}
	bool success = tree->add(part1Size, windowID);
	// if (success) {
	//		TODO: add to map<windowID:set<workspaceID>>
	//		map[windowID];
	// }
	return success;
}

bool Workspace::removeWindow(int windowID)
{
	bool success = tree->remove(windowID);
	// if (success) {
	//		TODO: add to map<windowID:set<workspaceID>>
	//		map.erase(windowID);
	// }
	return success;
}

void Workspace::renderTree(WindowNode* node, Area bounds)
{
	if (node != nullptr) {
		if (node->window->windowID !=
		    -1) { // node->isWindow() appears to be non functional
			server->setArea(node->window->windowID, bounds);
		} else {
			if (node->partVertically) {
				bounds.height -= node->part1Size; // restrict area to bottom size
				bounds.y += node->part1Size;      // select bottom area
				renderTree(node->part2, bounds);  // render bottom area

				bounds.height = node->part1Size;
				bounds.y -= node->part1Size;
				renderTree(node->part1, bounds); // render top section
			} else {
				bounds.width -= node->part1Size; // restrict area to right size
				bounds.x += node->part1Size;     // select right area
				renderTree(node->part2, bounds); // render right area

				bounds.width = node->part1Size;
				bounds.x -= node->part1Size;
				renderTree(node->part1, bounds); // render left section
			}
		}
	}
}

void Workspace::render()
{
	Area area = {0, 0, 600, 450}; //{0, 0, width, height};						// WARNINGL
	                              // WIDTH AND HEIGHT ARE NOT SET PROPERLY
	renderTree(tree->getRoot(), area);
}