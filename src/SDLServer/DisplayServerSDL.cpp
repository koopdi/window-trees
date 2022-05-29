#include "DisplayServerSDL.h"

int DisplayServerSDL::numScreensToConstruct = 1;

Area DisplayServerSDL::defaultWindowArea = {0, 0, 800, 600 };
void DisplayServerSDL::run() {
	//call init fn

	//event loop?
	while(true);
}


DisplayServerSDL::DisplayServerSDL() {
	atexit(SDL_Quit);
	SDL_Init(SDL_INIT_VIDEO);

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	defaultWindowArea = { 0, displayMode.h / 2,
	800, 600 };

	for (int i = 0; i < numScreensToConstruct; i++) {
		screens.push_back(ServerScreenSDL("WindowManager Demo Screen" + std::to_string(i),
			defaultWindowArea));
		defaultWindowArea.x += defaultWindowArea.width;
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
