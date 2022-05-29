#include "ServerScreenSDL.h"

int ServerScreenSDL::newWinID = 0;
ServerScreenSDL::ServerScreenSDL(std::string name, Area area) {
	win = SDL_CreateWindow(name.c_str(), area.x, area.y, area.width, area.height, 0);
	ren = SDL_CreateRenderer(win, -1, 0);
	tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
		area.width, area.height);
}

ServerScreenSDL::~ServerScreenSDL() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyTexture(tex);
	SDL_DestroyWindow(win);  //                                                                          IDK IF THIS IS A GOOD IDEA
}

