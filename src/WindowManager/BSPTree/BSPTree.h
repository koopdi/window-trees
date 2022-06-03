#include "ServerInterface.h"
#include "WindowTreeInteraface.h"
#include "WindowNode.h"

class BSPTree : public WindowTreeInterface
{
	virtual void render(ServerInterface* server) override;
	virtual void addWindow(long windowID) override;
	virtual void remWindow(long windowID) override;
};