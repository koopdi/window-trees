#pragma once

#include "ServerInterface.h"
//        ServerInterface.h

class WindowTreeInterface {
	virtual void render(ServerInterface* server) = 0;
	virtual void addWindow(long windowID)        = 0;
	virtual void remWindow(long windowID)        = 0;
	virtual void resize(Area area);
};