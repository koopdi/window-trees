#include "types.h"
#include "xtypes.h"
class ServerInterface
{
	virtual int getHeight(int screen, int windowID) const              = 0;
	virtual int getWidth(int screen, int windowID) const               = 0;
	virtual int getPosition(int screen, int windowID) const            = 0;
	virtual void setHeight(int screen, int windowID, int height)       = 0;
	virtual void setWidth(int screen, int windowID, int width)         = 0;
	virtual void setPosition(int screen, int windowID, Point position) = 0;

	virtual void setEventCallback(void update(XEvent& event))          = 0;
};