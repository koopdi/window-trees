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
	Area getArea(long windowID) override;
	Area getScreenSize(long screenID) override;
	std::vector<long> getScreens() override;
	std::vector<long> getWindows(long screenID) override;
	void setInitCallback(InitHandlerFn fn) override;
	void setEventCallback(EventHandlerFn fn) override;
	void run() override;
	void setHeight(int screen, int windowID, int height);
	void setWidth(int screen, int windowID, int width);
	void setPosition(int screen, int windowID, Point position);

	int getHeight(int screen, int windowID) const;
	int getWidth(int screen, int windowID) const;
	int getPosition(int screen, int windowID) const;

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