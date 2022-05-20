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

struct TreeQueryResult{
	bool success;
	Window root_return;
	Window parent_return;
	Window *children_return;
	unsigned int nchildren_return;
};

void XServer::init() {//														HALF IMPLEMENTED
	XSelectInput(display, DefaultRootWindow(display),
		SubstructureRedirectMask | SubstructureNotifyMask); //grab input from root window    		//SINGLE HEAD ONLY
	//maybe we can set up that map from ids to windows here :)

	Logger& logg = log;
	//set default callback for events (logger);
	handlerFunc = [logg](ServerInterface* server, XEvent* event) mutable {
		logg.warn(" >>> NO XEVENT HANDLER REGISTERED <<<\tDropped Event Type: \"" +
		std::to_string(event->type) + "\"");

		std::cout << "X Server Event: " << event->type << std::endl;
	};


	initFunc = [](ServerInterface* server){};

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
	initFunc(this);
	XUngrabServer(display); //unblock X Server
	eventLoop(); //enter event loop
}

void XServer::eventLoop() {//														HALF IMPLEMENTED
	while (running) {
		XEvent event;
		XNextEvent(display, &event);

		handlerFunc(this, &event);

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

	int screenCount = ScreenCount(display);
	log.verb("Display " + std::string(display_var) + " has "
		+ std::to_string(screenCount) + " screen(s).");

	log.verb("Getting default screen...");
	defaultScreeen = DefaultScreen(display);

	log.verb("Getting other screens...");
	for (int i = 0; i < screenCount; i++) {
		screens.push_back(XScreenOfDisplay(display, i));
	}

	init();
}

XServer::XServer(InitHandlerFn initFn, EventHandlerFn eventFn) {
	handlerFunc = eventFn;
	initFunc = initFn;
	XServer();
}

Area XServer::getArea(long windowID) {
	XWindowAttributes attrs;
	XGetWindowAttributes(display, (Window)windowID, &attrs);
	return Area {attrs.x, attrs.y, attrs.width, attrs.height};
}

void XServer::setArea(long windowID, Area area) {
	unsigned int areaBitmask = CWX | CWY | CWWidth | CWHeight;
	XWindowChanges changes;
	changes.x = area.x;
	changes.y = area.y;
	changes.width = area.width;
	changes.height = area.height;
	XConfigureWindow(display, (Window)windowID, areaBitmask, &changes);
}

std::vector<long> XServer::getScreens() {
	std::vector<long> screens;
	int numScreens = ScreenCount(display);
	for (int i = 0; i < numScreens; i++){ 											// I unironically have no idea
		screens.push_back(i);
	}
	return screens;
}

std::vector<long> XServer::getWindows(long screenID) { 						//NOT FUNCTIONAL?
	log.erro("XServer::getWindows() does not support functioning.");
	TreeQueryResult qry;
	Screen* screen = XScreenOfDisplay(display, screenID); //PROBLEM IS (PROBABLY) HERE (if there is one) I HAVE NO IDEA IF XScreenOfDisplay() takes these parameters
	qry.success = XQueryTree(display, screen->root,
		&qry.root_return, &qry.parent_return, &qry.children_return, &qry.nchildren_return);
	if(!qry.success){
		throw std::string("failed to query windows of screen");
	}
	std::vector<long> windows;

	for(int i = 0; i < qry.nchildren_return; i++){
		windows.push_back(qry.children_return[i]);
	}

	return windows;
}

void XServer::setEventCallback(EventHandlerFn fn) {
	handlerFunc = fn;
}

void XServer::setInitCallback(InitHandlerFn fn) {
	initFunc = fn;
}

XServer::~XServer(){
	XCloseDisplay(display);
	log.warn("The current destructor in Xserver.cpp does not free any memory itself");					//review this fact
}


