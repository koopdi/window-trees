#pragma once

// #include "ServerInterface.h"
#include "WindowTreeInterface.h"


class MasterStack : public WindowTreeInterface
{
private:
	WindowNode* head;
	windowNode* tail;
	Area area;
	int numWindows;
	int masterSize;
	bool vertical;
	void render(ServerInterface* server, MasterStackNode* node, int depth);

public:
	MasterStack(ServerInterfaceArea* server, Area workspaceSize = {0,0, 600, 800});
	virtual void render(ServerInterface* server) override;
	virtual void addWindow(long windowID) override;
	virtual void remWindow(long windowID) override;
	virtual void resize(Area area) override;
};