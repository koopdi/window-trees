#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H

#include "types.h"
#include "xtypes.h"
#include <functional>
#include <vector>

/**
 * @brief An abstract class that provides an interface for window
 * managmenet on any display server.
 */

class ServerInterface;

/// The display server calls this function,
///  when the window manager starts.
typedef std::function<void(ServerInterface* server)> InitHandlerFn;

/// The server calls this function when events are produced.
typedef std::function<void(XEvent* event)>
    EventHandlerFn;

class ServerInterface
{
public:
	// public methods ----------------------------------------

	/**
	 * @brief Set the shape and position of a window.
	 * @param windowID The window to set.
	 * @param area The shape and position to set.
	 */
	virtual void setArea(long windowID, Area area)      = 0;

	/**
	 * @brief Get the size and position of a window.
	 * @param windowID The window to get.
	 * @return Area The size and position of the window.
	 */
	virtual Area getArea(long windowID)                 = 0;

	/**
	 * @brief Get the size of a screen.
	 * @param screenID The screen to get.
	 * @return Area The size of the screen.
	 */
	virtual Area getScreenSize(long screenID)           = 0;

	/**
	 * @brief Get all available screens.
	 * @return std::vector<long> A collection of Screen IDs.
	 */
	virtual std::vector<long> getScreens()              = 0;

	/**
	 * @brief Get all available windows on a given screen.
	 * @param screenID The screen to get windows from.
	 * @return std::vector<long> A collection of Window IDs.
	 */
	virtual std::vector<long> getWindows(long screenID) = 0;

	/**
	 * @brief Register a function to be called.
	 * @param fn Called when the Window Manager starts.
	 */
	virtual void setInitCallback(InitHandlerFn fn)      = 0;

	/**
	 * @brief Set the Event Callback object.
	 * @param fn A function that accepts server events.
	 */
	virtual void setEventCallback(EventHandlerFn fn)    = 0;

	/**
	 * @brief We get signal, main screen turn on:
	 * it you.
	 */
	virtual void run()                                  = 0;

private:
	// private attributes ------------------------------------
	// private methods ---------------------------------------
};
#endif