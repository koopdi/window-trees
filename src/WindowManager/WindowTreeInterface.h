#include "ServerInterface.h"

class WindowTreeInterface {
	virtual void render(ServerInterface* server, Area wsArea) = 0;
	virtual void addWindow(long windowID)        = 0;
	virtual void remWindow(long windowID)        = 0;
};