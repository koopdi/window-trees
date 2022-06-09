#include "ServerInterface.h"
#include "types.h"
#include "Logger.h"
#include "ServerScreenSDL.h"
#include <vector>

enum ClickMode {
	ADD,
	DEL,
	ROT,
};

class DisplayServerSDL : public ServerInterface{
private:
	static int numScreensToConstruct;
	static Area defaultWindowArea;
	static int defaultWindowSpace;
	bool running;

	std::vector<ServerScreenSDL*> screens;

	ClickMode clickMode;
	void clickHandler(SDL_Event& e);

	EventHandlerFn handlerFunc;
	InitHandlerFn initFunc;

public:
	virtual Area getArea(long windowID) override;
	virtual void setArea(long windowID, Area area) override;
	virtual std::vector<long> getScreens() override;
	virtual std::vector<long> getWindows(long screenID) override;
	virtual Area getScreenSize(long screenID) override;

	virtual void setInitCallback(InitHandlerFn fn) override;
	virtual void setEventCallback(EventHandlerFn fn) override;
	virtual void run() override;


	DisplayServerSDL();
	DisplayServerSDL(InitHandlerFn initFn, EventHandlerFn eventFn);

	~DisplayServerSDL();
};