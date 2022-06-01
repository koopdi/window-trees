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

	ServerWindowSDL(SDL_Rect rect = {0,0,100,100}, SDL_Color color = {0xFF, 0x00, 0xFF, 0xFF});
	ServerWindowSDL();

private:
	static long nextID;
};