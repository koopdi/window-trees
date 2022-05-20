#include "types.h"
#include "xtypes.h"
#include <vector>
#include <functional>

typedef std::function<void(XEvent* event)> EventHandlerFn;

class ServerInterface
{
public:
	virtual int getHeight(int screen, int windowID) const              = 0;
	virtual int getWidth(int screen, int windowID) const               = 0;
	virtual Point getPosition(int screen, int windowID) const          = 0;
	virtual void setHeight(int screen, int windowID, int height)       = 0;
	virtual void setWidth(int screen, int windowID, int width)         = 0;
	virtual void setPosition(int screen, int windowID, Point position) = 0;
	virtual std::vector<int> getWindowsOnScreen(int screen)            = 0;
	virtual int getScreenCount()                                       = 0;

	virtual void setEventCallback(EventHandlerFn fn)                   = 0;
};