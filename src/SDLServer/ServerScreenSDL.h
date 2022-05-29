#include "SDL2/SDL.h"
#include <set>
#include <string>
#include <thread>
#include <functional>
#include "ServerWindowSDL.h"

class ServerScreenSDL {
private:
	static int newWinID;
	std::set<ServerWindowSDL> windows; //stores windows; NOTE: uses overloaded < to sort by depth
	std::thread* screenThread; //stores the event loop for this screen
	bool running;
	SDL_Renderer* ren;
	SDL_Window* win;
	SDL_Texture* tex;

	int eventLoop();

public:
	ServerScreenSDL(std::string name, Area area);
	~ServerScreenSDL();
};