#pragma once

#include "Logger.h"
#include "ServerInterface.h"
#include "types.h"
#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>

/**
 * @file XServer.h
 * @author Christen Spadavecchia
 * @date 6/10/2022
 * @brief
 * Provide an xserver backend to the server interface API.
 * @note
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

	//waits on events from the X server and processes them when they arise
	void eventLoop();
	//returns a default InitHandlerFn for XServer
	InitHandlerFn getDefaultInitFn();

public:
	//returns the area of the window with the given windowID
	virtual Area getArea(long windowID) override;
	//sets the area of the window with the given windowID
	virtual void setArea(long windowID, Area area) override;
	//returns a vector of screen IDs (longs)
	virtual std::vector<long> getScreens() override;
	//returns a vector of windowIDs for a screen identified by a given screenID
	virtual std::vector<long> getWindows(long screenID) override;
	//returns the size of a screen identified by a given screenID
	virtual Area getScreenSize(long screenID) override;
	//sets the function to be called when window management is about to begin
	virtual void setInitCallback(InitHandlerFn fn) override;
	//sets the function to be called when events are recieved
	//Note: this is usually a closure that calls an event handler method for a window manager class
	virtual void setEventCallback(EventHandlerFn fn) override;

	//sets up the event loop and then enteres it
	virtual void run() override;

	//constructs an XServer (ServerInterface backend)
	XServer();
	//constructs an XServer (ServerInterface backend) with the given init and event handlers
	XServer(InitHandlerFn initFn, EventHandlerFn eventFn);
	//cleans up the memory of an XServer (ServerInterface backend)
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