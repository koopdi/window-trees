#include "SDL2/SDL.h"
#include <set>
#include <unordered_map>
#include <string>
#include <thread>
#include <functional>
#include "ServerWindowSDL.h"
#include <iostream>

class ServerScreenSDL {
private:
	bool visible;
	int windowID;
	Area screenArea;
	//stores windows sorted by depth
	std::set<ServerWindowSDL*, ServerWindowSDL> windows;
	//stores windows
	std::unordered_map<long, ServerWindowSDL*> idWindowMap;
	SDL_Renderer* ren;
	SDL_Window* win;
	SDL_Texture* tex;

public:
	bool hasWindow(long windowID);
	bool isVisible();
	void handleEvent(SDL_Event& e);
	void render();
	void populateRandom(int num);

	long getScreenID();

	Area getArea(long windowID);
	void setArea(long windowID, Area area);
	std::vector<long> getWindows();
	Area getScreenSize();

	ServerScreenSDL(std::string name, Area area);
	~ServerScreenSDL();
};
