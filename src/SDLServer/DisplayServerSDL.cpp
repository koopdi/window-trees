#include "DisplayServerSDL.h"

int DisplayServerSDL::numScreensToConstruct = 3;
Area DisplayServerSDL::defaultWindowArea = { 0, 0, 400, 300 };
int DisplayServerSDL::defaultWindowSpace = 50;

void DisplayServerSDL::run()
{
	for (int i = 0; i < numScreensToConstruct; i++)
	{
		screens.push_back(new ServerScreenSDL(
		    "WindowManager Demo Screen" + std::to_string(i), defaultWindowArea));
		defaultWindowArea.x += defaultWindowArea.width + defaultWindowSpace;
	}

	// call init function
	initFunc(this);

	// event loop
	SDL_Event e;
	while (running)
	{

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				running = false;
				break;

			case SDL_KEYDOWN: // handle global shortcuts; falls through to windows
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					using namespace std;
					cout << "esc pressed" << endl;
					running = false;
				}

			case SDL_WINDOWEVENT:
				for (int i = 0; i < screens.size(); i++)
				{
					screens[i]->handleEvent(e);
				}
				break;

			default:
				std::cout << "DisplayServerSDL::run: dropped event of type ["
				          << std::to_string(e.type) << "]" << std::endl;
				break;
			}
		}
	}
}


DisplayServerSDL::DisplayServerSDL() : running(true) {
    atexit(SDL_Quit);
    SDL_Init(SDL_INIT_VIDEO);

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    defaultWindowArea = { 0, displayMode.h / 2,
    800, 600 };

    initFunc = [](ServerInterface* server){
        std::cout << "[Warning]: Falling back to default initFunc" << std::endl;
    };
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
