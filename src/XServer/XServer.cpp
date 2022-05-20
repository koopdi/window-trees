#include "XServer.h"

XServer::XServer() : log(Logger()){
	log.info("---Using X Server Backend---");

	log.verb("Getting $DISPLAY environment variable...");
	const char* display_var = std::getenv("DISPLAY");
	if(display_var == nullptr){
		log.exit("$DISPLAY not set; Exiting.");
	}

	log.verb("Opening X display...");
	if(!(display = XOpenDisplay(display_var))){
		log.exit("Failed to get X display; Exiting.");
	}

	int displayCount = XScreenCount(display);
	log.verb("Display" + std::string(display_var) + " has "
	+ std::to_string(displayCount) + "Displays.");

	log.verb("Getting displays...");
	defaultScreeen = DefaultScreen(display);

	// for(int i = 0; i < displayCount; i++){
	// 	screens.insert(XGetAtom)
	// }
}

int XServer::getHeight(int screen, int windowID) const {
	return 1;
}

int XServer::getWidth(int screen, int windowID) const {
	return 1;
}

Point XServer::getPosition(int screen, int windowID) const {
	return Point{0,0};
}

void XServer::setHeight(int screen, int windowID, int height) {
}

void XServer::setWidth(int screen, int windowID, int width) {

}

void XServer::setPosition(int screen, int windowID, Point position) {

}


void XServer::setEventCallback(void update(XEvent& ev)) {

}


