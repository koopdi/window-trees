#pragma once

// #include "xtypes.h"
#include "gchooser.h"
#include "gbutton.h"
#include "gwindow.h"
#include "SGLScreen.h"
#include "ServerInterface.h"


#include "types.h"

#include <map>
#include <memory>

/**
 * @brief The SGL Server acts as a system layer.
 * Mouse and keeb inputs are forwarded to the WindowManager.
 * Buttons are provided to simulate window creation/destruction
 * and those events are passed to the WindowManager.
 * The graphics are updated to reflect the layout of windows
 * on the active workspace.
 *
 * \todo emit window focus event when a window is selected
 */
class SGLServer : public ServerInterface
{
public:
	std::vector<SGLScreen> screens;

	SGLServer();
	/**
	 * @brief Set the Init Callback object
	 * Provides a concrete server interface.
	 * @param fn
	 */
	void setArea(long windowID, Area area) override;
		/**
	 * @brief Get the size and position of a window.
	 * @param windowID The window to get.
	 * @return Area The size and position of the window.
	 */
	Area getArea(long windowID) override;
		/**
	 * @brief Get the size of a screen.
	 * @param screenID The screen to get.
	 * @return Area The size of the screen.
	 */
	Area getScreenSize(long screenID) override;
		/**
	 * @brief Get all available screens.
	 * @return std::vector<long> A collection of Screen IDs.
	 */
	std::vector<long> getScreens() override;
		/**
	 * @brief Get all available windows on a given screen.
	 * @param screenID The screen to get windows from.
	 * @return std::vector<long> A collection of Window IDs.
	 */
	std::vector<long> getWindows(long screenID) override;
		/**
	 * @brief Register a function to be called.
	 * @param fn Called when the Window Manager starts.
	 */
	void setInitCallback(InitHandlerFn fn) override;
		/**
	 * @brief Set the Event Callback object.
	 * @param fn A function that accepts server events.
	 */
	void setEventCallback(EventHandlerFn fn) override;
		/**
	 * @brief We get signal, main screen turn on:
	 * it you.
	 */
	void run() override;
	/**
	 * @brief Set the Height object
	 *
	 * @param screen
	 * @param windowID
	 * @param height
	 */

	/**
	 * @brief check if a window exists
	 * @param windowID the window to check
	 * @return true if the window exists.
	 */
	bool contains(long windowID);

private:
	InitHandlerFn inFun;
	EventHandlerFn evFun;

	sgl::GWindow* window;
	const int WINDOW_WIDTH  = 640;
	const int WINDOW_HEIGHT = 480;

	std::map<long, winPtr> winDex;

	sgl::GChooser* dropDown;



	// private methods ---------------------------------------

	// remove a window
	void remove(long windowID = -1);
	// create a remove window event
	void evRemove(long windowID);
	// create a rotate event
	void evRotate(long windowID);

	// Handle mouse click events.
	void clickEv(sgl::GEvent ev);

	// Get the serverWindow that holds the provided gobject.
	winPtr getWin(sgl::GObject* obj);

	// select the window ID in the drop down chooser
	bool dropDownSelect(long windowID);

	// A function to remove windows when the drop down is clicked.
	void dropDownEv(sgl::GEvent ev);

	// A function to handle key events.
	void keyEv(sgl::GEvent ev);
	// A function to handle menu events.
	void menuEv(sgl::GEvent ev);
	// a function to handle gwindow evens
	void screenEv(sgl::GEvent ev);

	// Add buttons to the GWindow for sending events.
	void addButtons();
};