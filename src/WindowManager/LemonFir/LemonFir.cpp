#include "LemonFir.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

LemonFir::LemonFir(ServerInterface* server) : server(server) {}

void LemonFir::update(ev::Event& ev)
{
	try {
		cout << "Lemon Fir WM Update: ";
		if (ev.type == ev::EventType::ADD) {
			cout << "addWindow" << endl;
			addWindow(ev.add.winID);
		} else if (ev.type == ev::EventType::REMOVE) {
			cout << "remWindow" << endl;
			remWindow(ev.remove.winID);
		}

		render(server);

	} catch (string error) {
		cout << error << endl;
	}
}

void LemonFir::render(ServerInterface* server) {}

void LemonFir::addWindow(long windowID) {}

void LemonFir::remWindow(long windowID) {}

void LemonFir::resize(Area area) {}
