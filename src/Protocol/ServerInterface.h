#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H

#include "types.h"
#include "xtypes.h"
#include <vector>
#include <functional>

class ServerInterface;

typedef std::function<void(ServerInterface* server)> InitHandlerFn;
typedef std::function<void(ServerInterface* server, XEvent* event)> EventHandlerFn;

class ServerInterface
{
public:
	virtual void setArea(long windowID, Area area) 		= 0;
	virtual Area getArea(long windowID)					= 0;
	virtual Area getScreenSize(long screenID)			= 0;
	virtual std::vector<long> getScreens()				= 0;
	virtual std::vector<long> getWindows(long screenID)	= 0;

	virtual void setInitCallback(InitHandlerFn fn)		= 0;
	virtual void setEventCallback(EventHandlerFn fn)	= 0;
	virtual void run()									= 0;
};
#endif