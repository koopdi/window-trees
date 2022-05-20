#include "ServerInterface.h"
#include <iostream>
#include "Logger.h"
#include "types.h"
#include <vector>
#include <unordered_map>
#include <set>

// #define XSERVER_H //disable XServer

#ifndef XSERVER_H
#ifdef HAS_XLIB
#include <X11/Xlib.h>
#include <X11/extensions/randr.h>
#endif
class XServer : ServerInterface {
private:
    Display* display;
	Logger log;
	int defaultScreeen;
	std::vector<Screen*> screens; //acts as a map between int and Screen*
	std::unordered_map<Screen*, std::set<Window>> windowsPerScreenById;
	EventHandlerFn handlerFunc;
	InitHandlerFn initFunc;
	bool running = true;																		//is this bad style?

	void setXAttribute(unsigned int bitmask);

	void addWindow(Screen* screen, Window w);
	void removeWindow(Screen* screen, Window w);
	void init();
	void eventLoop();

public:
    virtual Area getArea(long windowID) override;
	virtual void setArea(long windowID, Area area) override;
	virtual std::vector<long> getScreens() override;
	virtual std::vector<long> getWindows(long screenID) override;
	virtual Area getScreenSize(long screenID) override;


	virtual void setInitCallback(InitHandlerFn fn) override;
    virtual void setEventCallback(EventHandlerFn fn) override;

    XServer();
	XServer(InitHandlerFn initFn, EventHandlerFn eventFn);

	~XServer();
};
#endif