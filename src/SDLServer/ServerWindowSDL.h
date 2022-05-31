#include "types.h"
#include "SDL2/SDL.h"
struct ServerWindowSDL
{
	long windowID;
	int depth;
	SDL_Rect rect;
	SDL_Color color;

	void render(SDL_Renderer * ren) const;
	bool operator==(ServerWindowSDL& win2);
	bool operator<(ServerWindowSDL& win2);

	ServerWindowSDL(long windowID, int depth, SDL_Rect rect, SDL_Color color);
};