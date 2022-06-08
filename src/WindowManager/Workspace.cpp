#include "Workspace.h"

#include <iostream>

Workspace::Workspace(ServerInterface* server, long screenID) : server(server),
	treeLayoutMode(ev::TreeMode::LEMON_FIR)
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
	for(auto [LAYOUT_MODE, layoutPtr] : windowTrees){
		std::cout << "WorkSpace addWindow: " << std::endl;
		layoutPtr->addWindow(windowID);
	}
}

void Workspace::remWindow(long windowID){
		for(auto [LAYOUT_MODE, layoutPtr] : windowTrees){
		std::cout << "WorkSpace remWindow: " << std::endl;
		layoutPtr->remWindow(windowID);
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
	if(mode == ev::TreeMode::PREV){
		std::vector<ev::TreeMode> modes = getAvailableModes();
		if(modes.size() > 1){
			for (int i = 0; i < modes.size() - 1; i++){
				if(modes[i+1] == treeLayoutMode){
					treeLayoutMode = modes[i];
				}
			}
		}

	} else if(mode == ev::TreeMode::NEXT) {
		auto iter = windowTrees.find(mode);
		if(iter != windowTrees.end() && ++iter != windowTrees.end()){
			mode = (*windowTrees.begin()).first;
		} else {
			mode = (*windowTrees.begin()).first;
		}

	} else {
		treeLayoutMode = mode;
	}
}


std::vector<ev::TreeMode> Workspace::getAvailableModes(){
	std::vector<ev::TreeMode> modes;
	for (auto [mode, ptr] : windowTrees){
		modes.push_back(mode);
	}
	return modes;
}

ev::TreeMode Workspace::getActiveMode(){
	return treeLayoutMode;
}