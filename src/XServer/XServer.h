#include "ServerInterface.h"
#include <iostream>
#include "Logger.h"
#include "types.h"
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
	std::set<int> screens;
public:
    virtual int getHeight(int screen, int windowID) const override;
    virtual int getWidth(int screen, int windowID) const override;
    virtual Point getPosition(int screen, int windowID) const override;
    virtual void setHeight(int screen, int windowID, int height) override;
    virtual void setWidth(int screen, int windowID, int width) override;
    virtual void setPosition(int screen, int windowID, Point position) override;

    virtual void setEventCallback(void update(XEvent& ev)) override;

    XServer();
};
#endif