#include "DisplayServerScreen.h"
#include "ServerInterface.h"
#include "xtypes.h"

/**
 * @brief
 *
 */
class DisplayServer : public ServerInterface{
public:
	std::vector<DisplayServerScreen> screens;

	void setArea(long windowID, Area area);
	Area getArea(long windowID);
	Area getScreenSize(long screenID);
	std::vector<long> getScreens();
	std::vector<long> getWindows(long screenID);

/**
 * @brief Set the Init Callback object
 * Provides a concrete server interface.
 * @param fn
 */
	void setInitCallback(InitHandlerFn fn);
	void setEventCallback(EventHandlerFn fn);
	void run() override;

	int getHeight(int screen, int windowID) const;
	int getWidth(int screen, int windowID) const;
	int getPosition(int screen, int windowID) const;
	void setHeight(int screen, int windowID, int height);
	void setWidth(int screen, int windowID, int width);
	void setPosition(int screen, int windowID, Point position);

	void setEventCallback(void update(XEvent& ev));

	DisplayServer();
private:
};