#include "LemonFir.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// ServerInterFace ---------------------------------------

LemonFir::LemonFir(ServerInterface* server)
    : server(server) //////////////////////
{
	// Create a root node.
	tree = std::make_shared<Split>();

	cout << tree->type << endl;

	halve = {2, 2, 2, 2};
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

// WindowTreeInterface -----------------------------------

void LemonFir::addWindow(long windowID)
{
	// cout << "addWindow" << endl;
	nextOpen() = std::make_shared<Pane>(windowID);
	print();
}

void LemonFir::remWindow(long windowID) { cout << "remWindow" << endl; }

void LemonFir::render(ServerInterface* server)
{
	// cout << "render" << endl;
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

// Private Methods ---------------------------------------

void LemonFir::print()
{
	cout << "\t\t--------Printing Tree ---------" << endl;
	print(tree);
}
void LemonFir::print(NodePtr node)
{
	if (node) {
		std::cout << node->type << endl;
		if (auto n = dynamic_cast<Split*>(node.get())) {
			print(n->left);
			print(n->right);
		} else if (auto n = dynamic_cast<Pane*>(node.get())) {
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
	} else if (auto n = dynamic_cast<Split*>(node.get())) {
		// attatch window here
		// cout << "split: " << n->type << endl;
		return nextOpen(n->right, cycles);
	} else if (auto n = dynamic_cast<Pane*>(node.get())) {
		// split this pane
		// cout << "pane: " << n->type << endl;
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
		if (auto n = dynamic_cast<Split*>(node.get())) {
			render(n->left, space, !vSplit);
			render(n->right, space, !vSplit);
		} else if (auto n = dynamic_cast<Pane*>(node.get())) {
			server->setArea(n->windowID, space);
			if (vSplit) {
				space.x += space.width / 2;
				space.width = space.width / 2;
			} else {
				space.y += space.height / 2;
				space.height = space.height / 2;
			}
		}
	}
}
