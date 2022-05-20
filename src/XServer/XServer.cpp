#include "XServer.h"

void XServer::init() {//														HALF IMPLEMENTED
	//maybe we can set up that map from ids to windows here :)

	//set default callback for events (logger);
	handler = [this](XEvent* event){
		log.warn(" >>> NO XEVENT HANDLER REGISTERED <<<\tDropped Event Type: \"" +
		std::to_string(event->type) + "\"");
	};

}

void XServer::eventLoop() {//														HALF IMPLEMENTED
	while (running) {
		XEvent event;
		XNextEvent(display, &event);

		handler(&event);

		//internal event handling
		switch (event.type)
		{
		case CreateNotify:
			break;

		case DestroyNotify:
			break;

		case ReparentNotify:
			break;

		case MapRequest:
			//framing could be done here
			XMapWindow(display, event.xmap.window); //make window visible
			break;

		case MapNotify:
			//returned when MapRequest is awknowledged by X server
			break;

		default:
			log.verb("[Window Manager]: dropped event of type \"" +
				std::to_string(event.type) + "\"");
		}

	}
}

XServer::XServer() : log(Logger()) {
	log.info("---Using X Server Backend---");

	log.verb("Getting $DISPLAY environment variable...");
	const char* display_var = std::getenv("DISPLAY");
	if (display_var == nullptr) {
		log.exit("$DISPLAY not set; Exiting.");
	}

	log.verb("Opening X display...");
	if (!(display = XOpenDisplay(display_var))) {
		log.exit("Failed to get X display; Exiting.");
	}

	int screenCount = XScreenCount(display);
	log.verb("Display" + std::string(display_var) + " has "
		+ std::to_string(screenCount) + " Displays.");

	log.verb("Getting displays...");
	defaultScreeen = DefaultScreen(display);

	for (int i = 0; i < screenCount; i++) {
		screens.push_back(XScreenOfDisplay(display, i));
	}

	XServer::~XServer();
	log.exit("Don't use bad software kids.");
	init();
	eventLoop();
}

XServer::XServer(EventHandlerFn fn) {
	handler = fn;
	XServer();
}

int XServer::getHeight(int screen, int windowID) const {//												NOT IMPLEMENTED

	return screen + windowID + 1;
}

int XServer::getWidth(int screen, int windowID) const {//												NOT IMPLEMENTED
	return screen + windowID + 1;
}

Point XServer::getPosition(int screen, int windowID) const { //												NOT IMPLEMENTED
	return Point{ screen, windowID };
}

void XServer::setHeight(int screen, int windowID, int height) {//												NOT IMPLEMENTED
	log.erro("setHeignt not implemented.\tParams:"
		+ std::to_string(screen) + ", "
		+ std::to_string(windowID) + ", "
		+ std::to_string(height) + ", ");
}

void XServer::setWidth(int screen, int windowID, int width) {//												NOT IMPLEMENTED
	log.erro("setWidth not implemented.\tParams:"
		+ std::to_string(screen) + ", "
		+ std::to_string(windowID) + ", "
		+ std::to_string(width) + ", ");
}

void XServer::setPosition(int screen, int windowID, Point position) {//										NOT IMPLEMENTED
	log.erro("setPosition not implemented.\tParams:"
		+ std::to_string(screen) + ", "
		+ std::to_string(windowID) + ", "
		+ + "x:" + std::to_string(position.x) + "y:" + std::to_string(position.y) + ", ");
}

std::vector<int> XServer::getWindowsOnScreen(int screen){//												NOT IMPLEMENTED
	std::vector<int> garbageData;
	garbageData.push_back(69);
	garbageData.push_back(420);
	garbageData.push_back(screen);
	return garbageData;
}

int XServer::getScreenCount(){
	return screens.size();
}

void XServer::setEventCallback(EventHandlerFn fn) {
	handler = fn;
}

XServer::~XServer(){
	XCloseDisplay(display);
	log.warn("The current destructor in Xserver.cpp does not free any memory itself");					//review this fact
}


