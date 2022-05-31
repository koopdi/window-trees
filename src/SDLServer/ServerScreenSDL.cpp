#include "ServerScreenSDL.h"

int ServerScreenSDL::newWinID = 0;


void ServerScreenSDL::handleEvent(SDL_Event& e) {
	if(e.window.windowID == windowID){
		if(e.type == SDL_WINDOWEVENT){
			switch (e.window.type){
				case SDL_WINDOWEVENT_CLOSE:
				SDL_HideWindow(win);
				break;

				case SDL_WINDOWEVENT_HIDDEN:
				visible = false;
				break;

				case SDL_WINDOWEVENT_SHOWN:
				visible = true;
				break;

				case SDL_WINDOWEVENT_EXPOSED:
				SDL_RenderPresent(ren);
				break;
			}
		} else { //must be a key event

		}
	}
}

ServerScreenSDL::ServerScreenSDL(std::string name, Area area) : visible(true){
	win = SDL_CreateWindow(name.c_str(), area.x, area.y, area.width, area.height, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, 0);
	tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
		area.width, area.height);

	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_RenderPresent(ren);

	windowID = SDL_GetWindowID(win);
}

ServerScreenSDL::~ServerScreenSDL() {
	for (int i = 0; i < windows.size(); i++) {
		/* send close events for all windows */
	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyTexture(tex);
	SDL_DestroyWindow(win);
}


