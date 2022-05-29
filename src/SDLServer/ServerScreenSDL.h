#include "SDL2/SDL.h"
#include <set>
#include <string>
#include "ServerWindowSDL.h"

class ServerScreenSDL {
private:
	static int newWinID;
	std::set<ServerWindowSDL> windows; //stores windows; NOTE: uses overloaded < to sort by depth
	SDL_Renderer* ren;
	SDL_Window* win;
	SDL_Texture* tex;
public:
	ServerScreenSDL(std::string name, Area area);
	~ServerScreenSDL();
};