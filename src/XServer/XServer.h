#pragma once

#include "xtypes.h"
#include "Logger.h"
#include "ServerInterface.h"
#include "types.h"
#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>

/**
 * @brief Provide an xserver backend to the server interface API.
 *
 * THIS BACKEND IS A PROOF OF CONCEPT TO SHOW THAT A REAL WORLD BACKEND IS POSSIBLE WITH
 * THE ABSTRACTIONS PROVIDED BY SERVERINTERFACE. A STABLE X BACKEND IS NOT IN SCOPE (for now).
 * As such, this backend is subject to strange behavior, does not support applications that
 * spawn X sub windows (most applications), and consequently mostly only supports a couple
 * terminal emulators.
 */

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

/** @brief
 *
 * XServer extends the abstract ServerInterface class and implements its virtual methods.
 * This window server uses XLib to tap into events from an X server and forward them to
 * the window manager.
*/
class XServer : public ServerInterface
{
private:
	//stores a pointer to an X display
	Display* display;
	//stores the logger for XServer
	Logger log;
	//stores the index of the default X screen
	int defaultScreeen;
	//stores pointers to each screen
	std::vector<Screen*> screens;
	//the max size for the char buffer for X11 errors
	const static int errorSize = 512;
	//stores the set of windows that exist on the X Server (helps prevent duplicate removes)
	std::unordered_set<long> windows;
	//if the event loop should continue
	bool running = true; // is this bad style?

	//function that is called to handle events
	EventHandlerFn handlerFunc;
	//function that is called to handle initialization
	InitHandlerFn initFunc;

	//converts X11 events to the internal event type
	ev::Event convertXEvent(XEvent& xEv);
	//handles X11 errors when they arise (bound in ctor)
	//signature determined by XErrorHandler type
	static int XErrorHandlerFn(Display* display, XErrorEvent* error);

	//waits on events from the X server
	void eventLoop();

public:
	virtual Area getArea(long windowID) override;
	virtual void setArea(long windowID, Area area) override;
	virtual std::vector<long> getScreens() override;
	virtual std::vector<long> getWindows(long screenID) override;
	virtual Area getScreenSize(long screenID) override;

	virtual void setInitCallback(InitHandlerFn fn) override;

	virtual void setEventCallback(EventHandlerFn fn) override;

	virtual void run() override;

	XServer();
	XServer(InitHandlerFn initFn, EventHandlerFn eventFn);

	~XServer();
};

//provides a type for storing XQueryTree results
struct TreeQueryResult
{
	bool success;
	Window root_return;
	Window parent_return;
	Window* children_return;
	unsigned int nchildren_return;
};