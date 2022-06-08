#include "Workspace.h"

#include <iostream>

Workspace::Workspace(ServerInterface* server, long screenID) : server(server),
	treeLayoutMode(ev::TreeMode::LEMON_FIR)
	{
	Area screenSize = server->getScreenSize(screenID);

	windowTrees[ev::TreeMode::LEMON_FIR] = new LemonFir(server);
	// windowTrees[ev::TreeMode::MASTER_STACK] = new MasterStack(server, screenSize);
	// windowTrees[ev::TreeMode::HEAP] = new HeapTree(server);
}

void Workspace::render(){
	windowTrees[treeLayoutMode]->render(server);
}

void Workspace::addWindow(long windowID){
	for(auto [LAYOUT_MODE, layoutPtr] : windowTrees){
		std::cout << "WorkSpace addWindow: " << std::endl;
		layoutPtr->addWindow(windowID);
	}
}

void Workspace::remWindow(long windowID){
	for(std::pair<ev::TreeMode,WindowTreeInterface*> pair : windowTrees){
		pair.second->addWindow(windowID);
	}
}

void Workspace::rotateSplit(long windowID){
	windowTrees[treeLayoutMode]->rotateSplit(windowID);
}

void Workspace::resize(Area area){
	for(std::pair<ev::TreeMode,WindowTreeInterface*> pair : windowTrees){
		pair.second->resize(area);
	}
}

void Workspace::setLayoutMode(ev::TreeMode mode){
	treeLayoutMode = mode;
	render();
}