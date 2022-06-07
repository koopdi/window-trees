#pragma once

#include "ServerInterface.h"
#include "WindowTreeInterface.h"
      // "WindowTreeInterface.h"
// #include "WindowNode.h"

class BSPTree : public WindowTreeInterface
{
private:
	WindowNode* root;
	Area area;
public:
	BSPTree();
	virtual void render(ServerInterface* server) override;
	virtual void addWindow(long windowID, WindowNode*& node);
	virtual void addWindow(long windowID) override;
	virtual void remWindow(long windowID) override;
	virtual void resize(Area area) override;
};