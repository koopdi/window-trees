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
	EventHandlerFn handler;
	bool running = true;																		//is this bad style?


	void addWindow(Screen* screen, Window w);
	void removeWindow(Screen* screen, Window w);
	void init();
	void eventLoop();

public:
    virtual int getHeight(int screen, int windowID) const override;
    virtual int getWidth(int screen, int windowID) const override;
    virtual Point getPosition(int screen, int windowID) const override;
    virtual void setHeight(int screen, int windowID, int height) override;
    virtual void setWidth(int screen, int windowID, int width) override;
    virtual void setPosition(int screen, int windowID, Point position) override;
	virtual std::vector<int> getWindowsOnScreen(int screen);
	virtual int getScreenCount();

    virtual void setEventCallback(EventHandlerFn fn) override;

    XServer();
	XServer(EventHandlerFn fn);

	~XServer();
};
#endif