#include "types.h"
#include "SDL2/SDL.h"
struct ServerWindowSDL
{
	long windowID;
	int depth;
	SDL_Rect rect;
	SDL_Color color;

	bool operator<(const ServerWindowSDL& win2);
	bool operator()(const ServerWindowSDL* l, const ServerWindowSDL* r) const;

	void render(SDL_Renderer * ren) const;
	ServerWindowSDL(SDL_Rect rect = {0,0,100,100}, SDL_Color color = {0xFF, 0x00, 0xFF, 0xFF});

private:
	static long nextID;
};

bool operator<(const ServerWindowSDL& win1, const ServerWindowSDL& win2);

