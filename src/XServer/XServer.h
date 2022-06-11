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
 * XServer extends the abstract ServerInterface class and implements its virtual methods.
 * This window server uses XLib to tap into events from an X server and forward them to
 * the window manager.
 *
 * THIS BACKEND IS A PROOF OF CONCEPT TO SHOW THAT A REAL WORLD BACKEND IS POSSIBLE WITH
 * THE ABSTRACTIONS PROVIDED BY SERVERINTERFACE. A STABLE X BACKEND IS NOT IN SCOPE (for now).
 * As such, this backend is subject to strange behavior, does not support applications that
 * spawn X sub windows (most applications), and consequently mostly only supports a couple
 * terminal emulators.
 */

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

/**
 * @brief An implementation of the server interface.
 *
 */

class XServer : public ServerInterface
{
private:
	Display* display;
	Logger log;
	int defaultScreeen;
	std::vector<Screen*> screens;
	std::unordered_map<Screen*, std::set<Window>> windowsPerScreenById;// map Screen* to windows
	const static int errorSize = 512;

	std::unordered_set<long> windows;

	EventHandlerFn handlerFunc;
	InitHandlerFn initFunc;
	bool running = true; // is this bad style?

	void setXAttribute(unsigned int bitmask);
	ev::Event convertXEvent(XEvent& xEv);
	XErrorHandler getXErrorHandler();

	void addWindow(Screen* screen, Window w);
	void removeWindow(Screen* screen, Window w);
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