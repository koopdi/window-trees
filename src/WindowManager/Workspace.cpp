#include "Workspace.h"

Workspace::Workspace(ServerInterface* server, long screenID) : server(server)
	{
	Area screenSize = server->getScreenSize(screenID);

	windowTrees[ev::TreeMode::LEMON_FIR] = new LemonFir(server);
	windowTrees[ev::TreeMode::MASTER_STACK] = new MasterStack(server, screenSize);
	// windowTrees[ev::TreeMode::HEAP] = new HeapTree(server);
}

void Workspace::render(){
	windowTrees[treeLayoutMode]->render(server);
}

void Workspace::addWindow(long windowID){
	for(pair<ev::TreeMode,WindowTreeInterface*> pair : windowTrees){
		pair.second.addWindow(windowID);
	}
}

void Workspace::remWindow(long windowID){
	for(pair<ev::TreeMode,WindowTreeInterface*> pair : windowTrees){
		pair.second.addWindow(windowID);
	}
}

void Workspace::rotateSplit(long windowID){
	windowTrees[treeLayoutMode]->rotateSplit(windowID);
}

void Workspace::resize(Area area){
	for(pair<ev::TreeMode,WindowTreeInterface*> pair : windowTrees){
		pair.second.addWindow(windowID);
	}
}

void Workspace::setLayoutMode(ev::TreeMode mode){
	treeLayoutMode = mode;
	render();
}