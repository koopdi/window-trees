#ifdef HAS_XLIB
#include "Logger.h"
#include "ServerInterface.h"
#include "types.h"
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

/**
 * @brief Provide an xserver backend to the server interface API.
 *
 */

// #define XSERVER_H //disable XServer

#ifndef XSERVER_H

#include <X11/Xlib.h>
#include <X11/extensions/randr.h>


/**
 * @brief An implementation of the server interface.
 *
 */

class XServer : public ServerInterface {
private:
	Display* display;
	Logger log;
	int defaultScreeen;
	std::vector<Screen*> screens; // acts as a map between int and Screen*
	std::unordered_map<Screen*, std::set<Window>> windowsPerScreenById;
	EventHandlerFn handlerFunc;
	InitHandlerFn initFunc;
	bool running = true; // is this bad style?

	void setXAttribute(unsigned int bitmask);

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
	XServer(InitHandlerk-uoFn initFn, EventHandlerFn eventFn);

	~XServer();
};

#endif
#endif