#include "ServerWindowSDL.h"

long ServerWindowSDL::nextID = 0;

ServerWindowSDL::ServerWindowSDL(SDL_Rect rect, SDL_Color color) : rect(rect), color(color) {
	depth = -nextID;
	windowID = nextID++;
}

void ServerWindowSDL::render(SDL_Renderer* ren) const {
	SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(ren, &rect);
}

bool operator<(const ServerWindowSDL& win1, const ServerWindowSDL& win2){
	return win1.depth < win2.depth;
}
