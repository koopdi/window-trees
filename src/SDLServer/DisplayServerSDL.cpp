#include "DisplayServerSDL.h"

int DisplayServerSDL::numScreensToConstruct = 3;
Area DisplayServerSDL::defaultWindowArea    = {0, 0, 400, 300};
int DisplayServerSDL::defaultWindowSpace    = 50;

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

	while (running && SDL_WaitEvent(&e))
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

		case SDL_MOUSEBUTTONDOWN:
		clickHandler(e);
			break;

		default:
			std::cout << "DisplayServerSDL::run: dropped event of type ["
			          << std::to_string(e.type) << "]" << std::endl;
			break;
		}

		if (running != false)
		{
			running = false;
			for (int i = 0; i < screens.size(); i++)
			{
				if (screens[i]->isVisible())
				{
					running = true;
				}
			}
		}
	}
}

DisplayServerSDL::DisplayServerSDL() : running(true)
{
	atexit(SDL_Quit);
	SDL_Init(SDL_INIT_VIDEO);

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	defaultWindowArea = {0, displayMode.h / 2, 800, 600};

	initFunc          = [](ServerInterface* server)
	{ std::cout << "[Warning]: Falling back to default initFunc" << std::endl; };
}

DisplayServerSDL::DisplayServerSDL(InitHandlerFn initFn, EventHandlerFn eventFn)
{
}

DisplayServerSDL::~DisplayServerSDL() {
	for (ServerScreenSDL* screen : screens){
		delete screen;
	}

}

Area DisplayServerSDL::getArea(long windowID) {
	for (int i = 0; i < screens.size(); i++){
		if(screens[i]->hasWindow(windowID)){
			return screens[i]->getArea(windowID);
		}
	}
}

void DisplayServerSDL::setArea(long windowID, Area area) {
	for (int i = 0; i < screens.size(); i++){
		if(screens[i]->hasWindow(windowID)){
			return screens[i]->setArea(windowID, area);
		}
	}
	throw std::string("[DisplayServerSDL] No window with ID "
		+ std::to_string(windowID) + "exists");
}

std::vector<long> DisplayServerSDL::getScreens() {
	std::vector<long> screenIDs;
	for(ServerScreenSDL* screen : screens) {
		screenIDs.push_back(screen->getScreenID());
	}
	return screenIDs;
}

std::vector<long> DisplayServerSDL::getWindows(long screenID) {
	for (int i = 0; i < screens.size(); i++){
		if(screens[i]->getScreenID() == screenID){
			return screens[i]->getWindows();
		}
	}

	throw std::string("[DisplayServerSDL] No screen with ID "
		+ std::to_string(screenID) + "exists");
}

Area DisplayServerSDL::getScreenSize(long screenID) {
	for (int i = 0; i < screens.size(); i++){
		if(screens[i]->getScreenID() == screenID){
			return screens[i]->getScreenSize();
		}
	}

	throw std::string("[DisplayServerSDL] No screen with ID "
		+ std::to_string(screenID) + "exists");
}

void DisplayServerSDL::setInitCallback(InitHandlerFn fn) {
	initFunc = fn;
}

void DisplayServerSDL::setEventCallback(EventHandlerFn fn) {
	handlerFunc = fn;
}
