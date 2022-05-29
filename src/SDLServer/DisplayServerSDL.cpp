Area DisplayServerSDL::getArea(long windowID) {

}

void DisplayServerSDL::setArea(long windowID, Area area) {

}

DisplayServerSDL:::vector<long> getScreens() {

}

DisplayServerSDL:::vector<long> getWindows(long screenID) {

}

Area DisplayServerSDL::getScreenSize(long screenID) {

}


virtual void setInitCallback(InitHandlerFn fn) {

}


void DisplayServerSDL::setEventCallback(EventHandlerFn fn) {

}


void DisplayServerSDL::run() {

}



DisplayServerSDL::DisplayServerSDL();
DisplayServerSDL::DisplayServerSDL(InitHandlerFn initFn, EventHandlerFn eventFn);

DisplayServerSDL::~DisplayServerSDL();