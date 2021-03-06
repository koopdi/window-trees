#include "XServer.h"
extern Logger glogger;

/**
 * @file XServer.h
 * @author Christen Spadavecchia
 * @date 6/10/2022
 * @brief Provide an implementation for the methods defined in XServer.h
 * Most notable functions:
 * -ctor - connects to X
 * -run - enters eventLoop
 * -eventLoop - handles events from the X server and informs the WM when necessary
 * -convertXEvent - converts events from XEvents to our internal event type
 */

//creates and returns a new internal Event from a given XEvent&
ev::Event XServer::convertXEvent(XEvent& xEv){
	ev::Event ev;

	switch(xEv.type){
		case ConfigureRequest: //windows request when want to be placed
		ev.type = ev::EventType::ADD;
		ev.add.winID = xEv.xconfigure.window;
		ev.add.winArea.x = xEv.xconfigure.x;
		ev.add.winArea.y = xEv.xconfigure.y;
		ev.add.winArea.width = xEv.xconfigure.width;
		ev.add.winArea.height = xEv.xconfigure.height;
		break;

		case DestroyNotify: //windows request this when they close
		ev.type = ev::EventType::REMOVE;
		ev.remove.winID = xEv.xdestroywindow.window;
		break;

		//mouse clicks
		case ButtonPress:
		case ButtonRelease:
		ev.type = ev::EventType::MOUSE;
		glogger.warn("Unideal mouse event conversion in convertXEvent");
		break;

		//keyboard presses
		case KeyPress:
		case KeyRelease:
		ev.type = ev::EventType::KEY;
		ev.key.isUpEv = xEv.xkey.state;
		ev.key.winID = xEv.xkey.window;
		glogger.warn("Unideal key event conversion in convertXEvent");
		break;

		//should not be entered
		default:
		glogger.erro("BAD XEVENT CONVERSION");
		throw std::string("Failed to convert XEvent");
		break;
	}
	ev.screenID = defaultScreeen; //supports only one screen
	return ev;
}

//initializes grabing of window events from X's root window
//calls init and enters the event loop
void XServer::run()
{ //														HALF IMPLEMENTED
	glogger.warn("The X backend is intended as a proof of concept");
	glogger.info("The X backend will not work for any windows that have children");

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

//returns a default InitHandlerFn so that this backend will function if no InitHandlerFn is set
InitHandlerFn XServer::getDefaultInitFn(){
	return [this](ServerInterface* server)
	{
		Area area = server->getArea(DefaultRootWindow(display));
		glogger.info("RESOLUTION:" + std::to_string(area.width) + "x" + std::to_string(area.height));
	};
}

//X event loop; calls XServer::handlerFunc when events deemed important are intercepted
//Note: automatically honnors MapRequest events (windows will appear as soon as they try to)
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
			glogger.info(
				"[XServerBackend]: dropped (likely dupe) destroy event for missing windowID " +
				std::to_string(event.xdestroywindow.window)
			);
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
			glogger.verb("[XServerBackend]: dropped event of type \"" +
			         std::to_string(event.type) + "\"");
		}
	}
}


//handler function for XLib errors (allows for recovery from some errors)
int XServer::XErrorHandlerFn(Display* display, XErrorEvent* error){
	char txtBuff[errorSize];

	XGetErrorText(display, error->error_code, txtBuff, errorSize);
	glogger.warn(std::string(txtBuff));

	switch (error->error_code){
	case BadWindow: //known recoverable error
		glogger.info("An invalid windowID reached the X Backend");
	break;

	case BadAccess: //known recoverable error
		glogger.verb("BadAccess is often reported on failure to bind to the X server");
		glogger.verb("Is an X server running on the correct display?");
		glogger.verb("TIP: relaunch the X server and this program");
		glogger.exit("Failed to gain access to critical X resource");
	break;

	default: //may be unrecoverable
		glogger.exit("This type of error is either unrecoverable or not in scope to be handled");
	}

	return 0;
}

//constructs an XServer (X Server ServerInterface)
//opens an X display with XLib
//sets default initFunc
//sets an XErrorHandler to allow recovery from recoverable errors
XServer::XServer()
{
	glogger.info("---Using X Server Backend---");

	glogger.verb("Getting $DISPLAY environment variable...");
	const char* display_var = ":9"; // std::getenv("DISPLAY");
	if (display_var == nullptr)
	{
		glogger.exit("$DISPLAY not set; Exiting.");
	}

	glogger.verb("Opening X display...");
	if (!(display = XOpenDisplay(display_var))) //open x display (connect to x server)
	{
		glogger.exit("Failed to get X display; Exiting.");
	}

	int screenCount = ScreenCount(display);
	glogger.verb("Display " + std::string(display_var) + " has " +
	         std::to_string(screenCount) + " screen(s).");

	glogger.verb("Getting default screen...");
	defaultScreeen = DefaultScreen(display);

	glogger.verb("Getting other screens...");
	for (int i = 0; i < screenCount; i++)
	{
		screens.push_back(XScreenOfDisplay(display, i)); //push screens to vector
	}

	initFunc = getDefaultInitFn(); //set init handler func
	XSetErrorHandler(&XErrorHandlerFn); //set XErrorHandler (for error recovery)
}

//Constructs an XServer (interface) with a predefiend InitHandlerFn and EventHandlerFn
//See other constructor for more info
XServer::XServer(InitHandlerFn initFn, EventHandlerFn eventFn)
{
	//register handler functions
	handlerFunc = eventFn;
	initFunc    = initFn;
	//call other ctor
	XServer();
}

//returns the area of the window with the given windowID
Area XServer::getArea(long windowID)
{
	XWindowAttributes attrs;
	XGetWindowAttributes(display, (Window)windowID, &attrs); //get attributes of window
	return Area{attrs.x, attrs.y, attrs.width, attrs.height}; //unpack relevant ones into an Area
}

//returns the size of the screen with the given screenID
Area XServer::getScreenSize(long screenID)
{
	//return area of root window using getArea
	return getArea(XRootWindowOfScreen(XScreenOfDisplay(display, screenID)));
}

//sets the dimensions of the window with the given windowID to the given area
void XServer::setArea(long windowID, Area area)
{
	unsigned int areaBitmask = CWX | CWY | CWWidth | CWHeight; //bitmask for changes to actually use
	XWindowChanges changes;
	changes.x      = area.x;
	changes.y      = area.y;
	changes.width  = area.width;
	changes.height = area.height;
	glogger.info("conf'd window with id:" + std::to_string(windowID));
	XConfigureWindow(display, (Window)windowID, areaBitmask, &changes);
}

//returns a vector of X screens on the current X Server
//Note: XRandR is often used for multihead instead of multiple real X Screens
//      this will only return actual X screens
std::vector<long> XServer::getScreens()
{
	std::vector<long> screens;
	int numScreens = ScreenCount(display);
	for (int i = 0; i < numScreens; i++)
	{ // screens are indexed serially in X
		screens.push_back(i);
	}
	return screens;
}

//returns a vector of windowIDs on the screen with the given screenID
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

//sets the function called when a convertable is produced by the X server
void XServer::setEventCallback(EventHandlerFn fn) { handlerFunc = fn; }

//sets the function to be called on initialization ( called during XServer::run() )
void XServer::setInitCallback(InitHandlerFn fn) { initFunc = fn; }

//cleans up memory after the XServer (ServerInterface Backend) is deleted
XServer::~XServer()
{
	XCloseDisplay(display); //close the X display (free XLib mem)
}
