#include "LemonFir.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

LemonFir::LemonFir(ServerInterface* server)
    : server(server), tree(nullptr) ///////
{
	tree = new Split();
	cout << tree->type << endl;
}

void LemonFir::update(ev::Event& ev)
{       // handle events sent by the server
	try { // print string exceptions and break
		if (ev.type == ev::EventType::ADD) {
			addWindow(ev.add.winID);
		} else if (ev.type == ev::EventType::REMOVE) {
			remWindow(ev.remove.winID);
		}

		render(server);

	} catch (string error) {
		cout << error << endl;
	}
}

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

void LemonFir::addWindow(long windowID) { cout << "addWindow" << endl; }

void LemonFir::remWindow(long windowID) { cout << "remWindow" << endl; }

void LemonFir::resize(Area area) { cout << "resize" << endl; }
