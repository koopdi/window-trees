#include "LemonFir.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// WindowManager -------------------------------------------
// WorkSpace -----------------------------------------------

LemonFir::LemonFir(ServerInterface* server)
    : server(server) //////////////////////
{
}

void LemonFir::update(ev::Event& ev)
{
	try { // Handle server events.
		if (ev.type == ev::EventType::ADD) {
			addWindow(ev.add.winID);
		} else if (ev.type == ev::EventType::REMOVE) {
			remWindow(ev.remove.winID);
		}

		render(server);

	} catch (string error) {
		// Print string exceptions and break.
		cout << error << endl;
	}
}

// WindowTreeInterface -------------------------------------

void LemonFir::addWindow(long windowID)
{
	// cout << "addWindow" << endl;
	nextOpen() = std::make_shared<Pane>(windowID);
	print();
}

void LemonFir::remWindow(long windowID) { cout << "remWindow" << endl; }

void LemonFir::render(ServerInterface* server)
{
	// there's no screen ID so passing -1
	// there's only one screen in sgl server and the ID is ignored.
	Area size = server->getScreenSize(-1);
	// cout << size;
	cout << "Scree Size:" << endl;
	cout << "x " << size.x << ", y " << size.y << endl;
	cout << "width " << size.width << ", height " << size.height << endl;

	render(tree, size);
}

void LemonFir::resize(Area area) { cout << "resize" << endl; }

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
		if (auto n = getSplit(node)) {
			print(n->left);
			print(n->right);
		} else if (auto n = getPane(node)) {
			cout << "ID: " << n->windowID << endl;
		}
	}
}

NodePtr& LemonFir::nextOpen()
{ // Begin search at the root.
	return nextOpen(tree);
}

NodePtr& LemonFir::nextOpen(NodePtr& node, int cycles)
{ // Recursively search until a null node is found.
	// cout << "nextOpen: " << cycles << endl;
	if (!node) {
		return node;
	} else if (auto n = getSplit(node)) {
		// attatch window here
		return nextOpen(n->right, cycles);
	} else if (getPane(node)) {
		// split this pane
		NodePtr temp = node;
		SplitPtr s   = std::make_shared<Split>();
		node         = s;
		s->left      = temp;
		return s->right;
	}
}

void LemonFir::render(NodePtr node, Area& space, bool vSplit)
{
	if (node) {
		if (auto n = getSplit(node)) {
			// Area old = space;
			if (vSplit) {
				space.width = space.width * (0.45);
			} else {
				space.height = space.height * (0.45);
			}
			render(n->left, space, !vSplit);
			if (vSplit) {
				space.x += space.width;
			} else {
				space.y += space.height;
			}
			render(n->right, space, !vSplit);
		} else if (auto n = getPane(node)) {
			server->setArea(n->windowID, space);
		}
	}
}
