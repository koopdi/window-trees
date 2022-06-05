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
	cout << "addWindow" << endl;
	nodePtr node = nextOpen();
	node = std::make_shared<Pane>(windowID);
}

void LemonFir::remWindow(long windowID) { cout << "remWindow" << endl; }

void LemonFir::render(ServerInterface* server)
{
	cout << "render" << endl;
	// there's no screen ID so passing -1
	// there's only one screen in sgl server and the ID is ignored.
	Area size = server->getScreenSize(-1);
	// cout << size;
	// cout << "Scree Size:" << endl;
	// cout << "x " << size.x << ", y " << size.y << endl;
	// cout << "width " << size.width << ", height " << size.height << endl;
}

void LemonFir::resize(Area area) { cout << "resize" << endl; }

// Private Methods ---------------------------------------

nodePtr LemonFir::nextOpen()
{ // Begin search at the root.
	return nextOpen(tree);
}

nodePtr LemonFir::nextOpen(nodePtr& node, int cycles)
{ // Recursively search until a null node is found.
	cout << "nextOpen: " << cycles << endl;
	if(!node)
	{
		return node;
	}
	else if(auto n = dynamic_cast<Split*>(node.get()))
	{ // attatch window here
		cout << "split: " << n->type << endl;
		return nextOpen(n->left, cycles);
	}
	else if(auto n = dynamic_cast<Pane*>(node.get()))
	{ // split this pane
		cout << "pane: " << n->type << endl;
		nodePtr temp = node;
		std::shared_ptr<Split> s = std::make_shared<Split>();
		node = s;
		s->left = temp;
		return s->right;
	}
}
