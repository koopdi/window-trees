#include "ServerScreenSDL.h"

int ServerScreenSDL::eventLoop() {

}

int ServerScreenSDL::newWinID = 0;
ServerScreenSDL::ServerScreenSDL(std::string name, Area area) : running(true) {
	win = SDL_CreateWindow(name.c_str(), area.x, area.y, area.width, area.height, 0);
	ren = SDL_CreateRenderer(win, -1, 0);
	tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
		area.width, area.height);

	auto eventLoop = [this]() {
		SDL_RenderCopy(ren, tex, NULL, NULL);
		SDL_RenderPresent(ren);

		SDL_Event e;
		while (running) {
			while (SDL_WaitEvent(&e)) {
				SDL_RenderCopy(ren, tex, NULL, NULL);
				SDL_RenderPresent(ren);

				switch (e.type) {
				case SDL_QUIT:
					return 0;

				case SDL_KEYDOWN:
					if (e.key.keysym.sym == SDLK_ESCAPE) return (0);

				}
			}
		}
		return 1;
	};

	screenThread = new std::thread(eventLoop);

}

ServerScreenSDL::~ServerScreenSDL() {
	for (int i = 0; i < windows.size(); i++) {
		/* send close events for all windows */
	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyTexture(tex);
	SDL_DestroyWindow(win);  //                                                                          IDK IF THIS IS A GOOD IDEA
}


