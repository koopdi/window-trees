#include "XServer.h"

/**
 * @brief Provide an implementation for the methods defined in XServer.h
 * Most notable functions:
 * -ctor - connects to X
 * -run - enters eventLoop
 * -eventLoop - handles events from the X server and informs the WM when necessary
 * -convertXEvent - converts events from XEvents to our internal event type
 */
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
		log.warn("Unideal mouse event conversion in convertXEvent");
		break;

		case KeyPress:
		case KeyRelease:
		ev.type = ev::EventType::KEY;
		ev.key.isUpEv = xEv.xkey.state; //maybe
		ev.key.winID = xEv.xkey.window;
		log.warn("Unideal key event conversion in convertXEvent");
		break;

		default:
		log.erro("BAD XEVENT CONVERSION");
		throw std::string("Failed to convert XEvent");
		break;
	}
	ev.screenID = defaultScreeen; //supports only one screen
	return ev;
}

void XServer::run()
{ //														HALF IMPLEMENTED
	log.warn("The X backend is intended as a proof of concept");
	log.info("The X backend will not work for any windows that have children");

	XSelectInput(display,
	             DefaultRootWindow(display),
	             SubstructureRedirectMask |
	                 SubstructureNotifyMask); // grab input from root window
	                                          // //SINGLE HEAD ONLY

	XGrabServer(display); // block X Server
	initFunc(this);
	XUngrabServer(display); // unblock X Server
	eventLoop(); // enter event loop
}

InitHandlerFn XServer::getDefaultInitFn(){
	return [this](ServerInterface* server)
	{
		Area area = server->getArea(DefaultRootWindow(display));
		log.info("RESOLUTION:" + std::to_string(area.width) + "x" + std::to_string(area.height));
	};
}

void XServer::eventLoop()
{
	while (running)
	{
		XEvent event;
		XNextEvent(display, &event);

		// event handling
		ev::Event genEv;

		switch (event.type)
		{
		case DestroyNotify:
		if(!windows.count(event.xdestroywindow.window)){
			log.info("[XServerBackend]: dropped (likely dupe) destroy event for missing windowID " +
				std::to_string(event.xdestroywindow.window));
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



int XServer::XErrorHandlerFn(Display* display, XErrorEvent* error){
	char txtBuff[errorSize];
	Logger logger;

	XGetErrorText(display, error->error_code, txtBuff, errorSize);
	logger.warn(std::string(txtBuff));

	switch (error->error_code){
	case BadWindow:
		logger.info("An invalid windowID reached the X Backend");
	break;

	case BadAccess:
		logger.verb("BadAccess is often reported on failure to bind to the X server");
		logger.verb("Is an X server running on the correct display?");
		logger.verb("TIP: relaunch the X server and this program");
		logger.exit("Failed to gain access to critical X resource");
	break;

	default:
		logger.exit("This type of error is either unrecoverable or not in scope to be handled");
	}

	return 0;
}

XServer::XServer()
{
	Logger log = Logger(std::cout, LogLevel::VERBOSE);
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

	initFunc = getDefaultInitFn();
	XSetErrorHandler(&XErrorHandlerFn);
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
{
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
}
