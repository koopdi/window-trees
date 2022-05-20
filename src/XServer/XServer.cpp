#include "XServer.h"


/* Configure window value mask bits */
#define CWX		(1<<0)
#define CWY		(1<<1)
#define CWWidth		(1<<2)
#define CWHeight	(1<<3)
#define CWBorderWidth	(1<<4)
#define CWSibling	(1<<5)
#define CWStackMode	(1<<6)

struct iFogor{
	XWindowChanges changes;
	unsigned int changeBitmask;
};

iFogor what(Screen* screen){
	iFogor fogor;
	fogor.changes.x = 0;
	fogor.changes.y = 0;
	fogor.changes.height = XHeightOfScreen(screen);
	fogor.changes.width = XWidthOfScreen(screen);

	fogor.changeBitmask = CWX | CWY | CWWidth | CWHeight;
	return fogor;
}
void XServer::init() {//														HALF IMPLEMENTED
	XSelectInput(display, DefaultRootWindow(display),
		SubstructureRedirectMask | SubstructureNotifyMask); //grab input from root window    		//SINGLE HEAD ONLY
	//maybe we can set up that map from ids to windows here :)

	Logger& logg = log;
	//set default callback for events (logger);
	handler = [logg](XEvent* event) mutable {
		logg.warn(" >>> NO XEVENT HANDLER REGISTERED <<<\tDropped Event Type: \"" +
		std::to_string(event->type) + "\"");

		std::cout << "X Server Event: " << event->type << std::endl;
	};

	XGrabServer(display); //block X Server

	Window returned_root;
	Window returned_parent;
	Window* top_level_windows;
	unsigned int num_top_level_windows;
	XQueryTree(display, DefaultRootWindow(display),
		&returned_root, &returned_parent, &top_level_windows, &num_top_level_windows);
	log.info("top level windows:" + std::to_string(num_top_level_windows));

	for(int i = 0; i < num_top_level_windows; i++){
		Window win = top_level_windows[i];
		XWindowAttributes returned_attrs;
		XGetWindowAttributes(display, win, &returned_attrs);
		log.verb("New Window Height: " + std::to_string(returned_attrs.height));
	}

	log.info("This would be a good time to do any sort of init callback");
	XUngrabServer(display); //unblock X Server
}

void XServer::eventLoop() {//														HALF IMPLEMENTED
	while (running) {
		XEvent event;
		XNextEvent(display, &event);

		handler(&event);

		iFogor bitMaskAndChanges = what(screens[0]);

		//internal event handling
		switch (event.type)
		{
		case CreateNotify:
			// XConfigureWindow(display, event.xconfigurerequest.window, bitMaskAndChanges.changeBitmask, &bitMaskAndChanges.changes);
			break;
		case DestroyNotify:
			break;

		case ReparentNotify:
			break;

		case ConfigureNotify:

			break;

		case ConfigureRequest:
			XConfigureWindow(display, event.xconfigurerequest.window, bitMaskAndChanges.changeBitmask, &bitMaskAndChanges.changes);
			break;

		case MapRequest:
			//framing could be done here
			XMapWindow(display, event.xmap.window); //make window visible
			break;

		case MapNotify:
			//returned when MapRequest is awknowledged by X server
			break;

		case UnmapNotify:
			//when a window disappears
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
	const char* display_var = ":9";//std::getenv("DISPLAY");
	if (display_var == nullptr) {
		log.exit("$DISPLAY not set; Exiting.");
	}

	log.verb("Opening X display...");
	if (!(display = XOpenDisplay(display_var))) {
		log.exit("Failed to get X display; Exiting.");
	}

	int screenCount = XScreenCount(display);
	log.verb("Display " + std::string(display_var) + " has "
		+ std::to_string(screenCount) + " screen(s).");

	log.verb("Getting default screen...");
	defaultScreeen = DefaultScreen(display);

	log.info("Default Screen Name = " + std::string(XDisplayName(display_var)));

	log.verb("Getting other screens...");
	for (int i = 0; i < screenCount; i++) {
		screens.push_back(XScreenOfDisplay(display, i));
	}

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


