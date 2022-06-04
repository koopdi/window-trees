#include "LemonFir.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

LemonFir::LemonFir(ServerInterface* server) : server(server) {}

void LemonFir::update(ev::Event& ev)
{
	try {
		// cout << "Lemon Fir WM Update: ";
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

void LemonFir::render(ServerInterface* server) { cout << "render" << endl; }

void LemonFir::addWindow(long windowID) { cout << "addWindow" << endl; }

void LemonFir::remWindow(long windowID) { cout << "remWindow" << endl; }

void LemonFir::resize(Area area) { cout << "resize" << endl; }
