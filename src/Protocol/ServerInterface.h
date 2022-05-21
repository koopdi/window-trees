#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H

#include "types.h"
#include "xtypes.h"
#include <vector>
#include <functional>

/**
 * @brief An abstract class that provides an interface for window
 * managmenet on any display server.
 */

class ServerInterface;

/// The display server calls this function, when the window manager starts.
typedef std::function<void(ServerInterface* server)> InitHandlerFn;
/// The server calls this function when events are produced.
typedef std::function<void(ServerInterface* server, XEvent* event)> EventHandlerFn;

class ServerInterface
{
public:
	virtual void setArea(long windowID, Area area) 		= 0;
	virtual Area getArea(long windowID)					= 0;
	virtual Area getScreenSize(long screenID)			= 0;
	virtual std::vector<long> getScreens()				= 0;
	virtual std::vector<long> getWindows(long screenID)	= 0;

/**
 * @brief Set the Init Callback object
 * Provides a concrete server interface.
 * @param fn
 */
	virtual void setInitCallback(InitHandlerFn fn)		= 0;
	virtual void setEventCallback(EventHandlerFn fn)	= 0;
};
#endif