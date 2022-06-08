#include "XServer.h"
using namespace std;
struct TreeQueryResult
{
	bool success;
	Window root_return;
	Window parent_return;
	Window* children_return;
	unsigned int nchildren_return;
};

ev::Event XServer::convertXEvent(XEvent& xEv){
	ev::Event ev;

	switch(xEv.type){
		case ConfigureRequest:
		ev.type = ev::EventType::ADD;
		ev.add.winID = xEv.xconfigure.window;
		ev.add.winArea.x = xEv.xconfigure.x;
		ev.add.winArea.y = xEv.xconfigure.y;
		ev.add.winArea.width = xEv.xconfigure.width;
		ev.add.winArea.height = xEv.xconfigure.height;
		break;

		case DestroyNotify:
		ev.type = ev::EventType::REMOVE;
		ev.remove.winID = xEv.xdestroywindow.window;
		break;

		case ButtonPress:
		case ButtonRelease:
		ev.type = ev::EventType::MOUSE;
		log.warn("Shitty mouse event conversion in convertXEvent");
		break;

		case KeyPress:
		case KeyRelease:
		ev.type = ev::EventType::KEY;
		ev.key.isUpEv = xEv.xkey.state; //maybe
		ev.key.winID = xEv.xkey.window;
		log.warn("Shitty key event conversion in convertXEvent");
		break;

		default:
		log.erro("BAD XEVENT CONVERSION");
		throw string("Failed to convert XEvent");
		break;
	}
	ev.screenID = defaultScreeen; //supports only one screen
	return ev;
}

void XServer::run()
{ //														HALF IMPLEMENTED
	XSelectInput(display,
	             DefaultRootWindow(display),
	             SubstructureRedirectMask |
	                 SubstructureNotifyMask); // grab input from root window
	                                          // //SINGLE HEAD ONLY

	// handlerFunc = [this](XEvent* event) mutable
	// {
	// 	cout << "xserver self event ding?" << endl;
	// 	if (event->type == ConfigureRequest)
	// 	{
	// 		setArea(event->xconfigurerequest.window, Area{0, 0, 400, 200});
	// 	}
	// };

	initFunc = [this](ServerInterface* server)
	{
		Area area = server->getArea(DefaultRootWindow(display));
		std::cout << "RESOLUTION:" << area.width << "x" << area.height << std::endl;
	};

	XGrabServer(display); // block X Server
	initFunc(this);
	XUngrabServer(display); // unblock X Server
	cout << "entering event loop" << endl;
	eventLoop(); // enter event loop
}

void XServer::eventLoop()
{ //														HALF IMPLEMENTED
	while (running)
	{
		cout << "loopding" << endl;
		XEvent event;
		cout << "getting next event" << endl;
		XNextEvent(display, &event);
		cout << "got next event" << endl;

		// event handling
		ev::Event genEv;

		switch (event.type)
		{
		case DestroyNotify:						//CRITICAL CASE DISABLED FOR TESTING
		if(!windows.count(event.xdestroywindow.window)){
			log.info("[XServerBackend]: dropped duplicate destroy event for windowID "
				+ std::to_string(event.xdestroywindow.window));
			break;
		} else {
			windows.erase(event.xdestroywindow.window);
		}
		case ConfigureRequest:
		if(event.type == ConfigureRequest){
			windows.insert(event.xconfigurerequest.window);
		}
		case ButtonPress:
		case ButtonRelease:
		case KeyPress:
		case KeyRelease:
		genEv = convertXEvent(event);
		handlerFunc(&genEv);
		break;

		case CreateNotify:
		case MapNotify:   // returned when MapRequest is awknowledged by X server
		case UnmapNotify: // when a window disappears
		case ReparentNotify: //when a window is reparented
			break;

		case MapRequest:
			// framing could be done here
			XMapWindow(display, event.xmap.window); // make window visible
			break;

		default:
			log.verb("[XServerBackend]: dropped event of type \"" +
			         std::to_string(event.type) + "\"");
		}
	}
}

XServer::XServer() : log(Logger())
{
	log.info("---Using X Server Backend---");

	log.verb("Getting $DISPLAY environment variable...");
	const char* display_var = ":9"; // std::getenv("DISPLAY");
	if (display_var == nullptr)
	{
		log.exit("$DISPLAY not set; Exiting.");
	}

	log.verb("Opening X display...");
	if (!(display = XOpenDisplay(display_var)))
	{
		log.exit("Failed to get X display; Exiting.");
	}

	int screenCount = ScreenCount(display);
	log.verb("Display " + std::string(display_var) + " has " +
	         std::to_string(screenCount) + " screen(s).");

	log.verb("Getting default screen...");
	defaultScreeen = DefaultScreen(display);

	log.verb("Getting other screens...");
	for (int i = 0; i < screenCount; i++)
	{
		screens.push_back(XScreenOfDisplay(display, i));
	}
}

XServer::XServer(InitHandlerFn initFn, EventHandlerFn eventFn)
{
	handlerFunc = eventFn;
	initFunc    = initFn;
	XServer();
}

Area XServer::getArea(long windowID)
{
	XWindowAttributes attrs;
	XGetWindowAttributes(display, (Window)windowID, &attrs);
	return Area{attrs.x, attrs.y, attrs.width, attrs.height};
}

Area XServer::getScreenSize(long screenID)
{
	return getArea(XRootWindowOfScreen(XScreenOfDisplay(display, screenID)));
}

void XServer::setArea(long windowID, Area area)
{
	unsigned int areaBitmask = CWX | CWY | CWWidth | CWHeight;
	XWindowChanges changes;
	changes.x      = area.x;
	changes.y      = area.y;
	changes.width  = area.width;
	changes.height = area.height;
	log.info("conf'd window with id:" + std::to_string(windowID));
	XConfigureWindow(display, (Window)windowID, areaBitmask, &changes);
}

std::vector<long> XServer::getScreens()
{
	std::vector<long> screens;
	int numScreens = ScreenCount(display);
	for (int i = 0; i < numScreens; i++)
	{ // I unironically have no idea
		screens.push_back(i);
	}
	return screens;
}

std::vector<long> XServer::getWindows(long screenID)
{ // NOT FUNCTIONAL?
	log.erro("XServer::getWindows() does not support functioning.");
	TreeQueryResult qry;
	Screen* screen = XScreenOfDisplay(
	    display,
	    screenID); // PROBLEM IS (PROBABLY) HERE (if there is one) I HAVE
	               // NO IDEA IF XScreenOfDisplay() takes these parameters
	qry.success = XQueryTree(display,
	                         screen->root,
	                         &qry.root_return,
	                         &qry.parent_return,
	                         &qry.children_return,
	                         &qry.nchildren_return);
	if (!qry.success)
	{
		throw std::string("failed to query windows of screen");
	}
	std::vector<long> windows;

	for (int i = 0; i < qry.nchildren_return; i++)
	{
		windows.push_back(qry.children_return[i]);
	}

	XFree(qry.children_return); // prevent returned child windows from being
	                            // leaked
	return windows;
}

void XServer::setEventCallback(EventHandlerFn fn) { handlerFunc = fn; }

void XServer::setInitCallback(InitHandlerFn fn) { initFunc = fn; }

XServer::~XServer()
{
	XCloseDisplay(display);
	log.warn(
	    "The current destructor in Xserver.cpp does not free any memory itself"); // review this fact
}
