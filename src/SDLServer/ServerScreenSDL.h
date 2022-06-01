#include "SDL2/SDL.h"
#include <set>
#include <string>
#include <thread>
#include <functional>
#include "ServerWindowSDL.h"
#include <iostream>

class ServerScreenSDL {
private:
	bool visible;
	int windowID;
	std::set<ServerWindowSDL> windows; //stores windows; NOTE: uses overloaded < to sort by depth

	SDL_Renderer* ren;
	SDL_Window* win;
	SDL_Texture* tex;

public:
	void handleEvent(SDL_Event& e);
	void render();

	void populateRandom(int num);


	ServerScreenSDL(std::string name, Area area);
	~ServerScreenSDL();
};