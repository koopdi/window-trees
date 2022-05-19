#include "ServerInterface.h"
#include "xtypes.h"

class DisplayServer : ServerInterface{
    vector<DisplayServerScreen> screens;

    virtual int getHeight(int screen, int windowID) const override;
    virtual int getWidth(int screen, int windowID) const override;
    virtual int getPosition(int screen, int windowID) const override;
    virtual void setHeight(int screen, int windowID, int height) override;
    virtual void setWidth(int screen, int windowID, int width) override;
    virtual void setPosition(int screen, int windowID, Point position) override;

    virtual void setEventCallback(void update(XEvent& ev)) override;

    DisplayServer();
};