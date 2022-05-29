#include "DisplayServerSDL.h"

int DisplayServerSDL::numScreensToConstruct = 1;
Area DisplayServerSDL::defaultWindowArea = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	800, 600 };

void DisplayServerSDL::run() {

}


DisplayServerSDL::DisplayServerSDL() {
	atexit(SDL_Quit);
	SDL_Init(SDL_INIT_VIDEO);
	for (int i = 0; i < numScreensToConstruct; i++) {
		screens.push_back(ServerScreenSDL("WindowManager Demo Screen" + std::to_string(i),
			defaultWindowArea));
	}

}

DisplayServerSDL::DisplayServerSDL(InitHandlerFn initFn, EventHandlerFn eventFn) {

}


DisplayServerSDL::~DisplayServerSDL() {

}

Area DisplayServerSDL::getArea(long windowID) {

}

void DisplayServerSDL::setArea(long windowID, Area area) {

}

std::vector<long> DisplayServerSDL::getScreens() {

}

std::vector<long> DisplayServerSDL::getWindows(long screenID) {

}

Area DisplayServerSDL::getScreenSize(long screenID) {

}


void DisplayServerSDL::setInitCallback(InitHandlerFn fn) {

}


void DisplayServerSDL::setEventCallback(EventHandlerFn fn) {

}
