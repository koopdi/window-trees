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

bool ServerWindowSDL::operator==(ServerWindowSDL& win2) {
	return windowID == win2.windowID;
}

bool ServerWindowSDL::operator<(ServerWindowSDL& win2) {
	return depth < win2.depth;
}
