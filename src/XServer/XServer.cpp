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
		handlerFunc(&event);

		// internal event handling
		switch (event.type)
		{
		case CreateNotify:
		case DestroyNotify:
		case ReparentNotify:
		case ConfigureNotify:
		case ConfigureRequest:
		case MapNotify:   // returned when MapRequest is awknowledged by X server
		case UnmapNotify: // when a window disappears
			break;

		case MapRequest:
			// framing could be done here
			XMapWindow(display, event.xmap.window); // make window visible
			break;

		default:
			log.verb("[Window Manager]: dropped event of type \"" +
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
