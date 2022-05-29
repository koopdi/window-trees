#include "SDL2/SDL.h"
#include <set>
#include "ServerWindowSDL.h"

class ServerScreenSDL {
private:
	std::set<ServerWindowSDL> windows;
	SDL_Renderer* ren;
	SDL_Window* win;
	SDL_Texture* tex;
public:

};