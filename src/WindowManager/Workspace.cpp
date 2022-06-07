#include "Workspace.h"

Workspace(ServerInterface* server, long screenID) : server(server), screenID(screenID),
	{
	Area screenSize = server->getScreenSize(screenID);

	windowTrees[ev::TreeMode::LEMON_FIR] = new LemonFir(server);
	windowTrees[ev::TreeMode::MASTER_STACK] = new MasterStack(server, screenSize);
	// windowTrees[ev::TreeMode::HEAP] = new HeapTree(server);
}

void render(){
	windowTrees[treeLayoutMode]->render(server);
}

void addWindow(long windowID){
	for(pair<ev::TreeMode,WindowTreeInterface*> pair : windowTrees){
		pair.second.addWindow(windowID);
	}
}

void remWindow(long windowID){
	for(pair<ev::TreeMode,WindowTreeInterface*> pair : windowTrees){
		pair.second.addWindow(windowID);
	}
}

void rotateSplit(long windowID){
	windowTrees[treeLayoutMode]->rotateSplit(windowID);
}

void resize(Area area){
	for(pair<ev::TreeMode,WindowTreeInterface*> pair : windowTrees){
		pair.second.addWindow(windowID);
	}
}

void setLayoutMode(ev::TreeMode mode){
	treeLayoutMode = mode;
	render();
}