#pragma once

// #include "ServerInterface.h"
#include "WindowTreeInterface.h"
#include "MasterStackNode.h"
#include <string>

class MasterStack : public WindowTreeInterface
{
private:
	MasterStackNode* head;
	MasterStackNode* tail;
	Area area;
	int numWindows;
	int masterSize;
	bool vertical;
	ServerInterface* server;
	void render(MasterStackNode* node, int depth);

public:
	MasterStack(ServerInterface* server, Area workspaceSize = {0,0, 600, 800});
	virtual void render(ServerInterface* server) override;
	virtual void addWindow(long windowID) override;
	virtual void remWindow(long windowID) override;
	virtual void resize(Area area) override;
	virtual void rotateSplit(long windowID) override;
};