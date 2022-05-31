#include "ServerWindowSDL.h"

ServerWindowSDL::ServerWindowSDL(long windowID, int depth, SDL_Rect rect, SDL_Color color) :
	windowID(windowID), depth(depth), rect(rect), color(color){}

void ServerWindowSDL::render(SDL_Renderer * ren) const{
	SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(ren, &rect);
}

bool ServerWindowSDL::operator==(ServerWindowSDL& win2){
	return depth == win2.depth;
}

bool ServerWindowSDL::operator<(ServerWindowSDL& win2){
	return depth < win2.depth;
}
