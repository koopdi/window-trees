#pragma once

#include "SGLServerScreen.h"
#include "ServerInterface.h"
#include "types.h"
#include "xtypes.h"

/**
 * @brief
 *
 */
class SGLServer : public ServerInterface
{
public:
	std::vector<SGLServerScreen> screens;

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

private:
	EventHandlerFn evFun;
};