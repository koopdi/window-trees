#include "Workspace.h"

Workspace::Workspace(int workspaceID) {}

int Workspace::getHeight() const {
	return height;
}
int Workspace::getWidth() const {
	return width;
}
Point Workspace::getPosition() const {
	return position;
}
int Workspace::getNumWindows() const {
	return numWindows;
}

void Workspace::setHeight(int height) {
	this->height = height;
}
void Workspace::setWidth(int width) {
	this->width = width;
}
void Workspace::setPosition(Point position) {
	this->position = position;
}
// bool Workspace::addWindow() {
// 	// bool success = tree->add();
// 	// if (success) {
// 	//		TODO: add to map<windowID:set<workspaceID>>
// 	//		map[windowID];
// 	// }
// 	return success;
// }
bool Workspace::removeWindow(int windowID) {
	bool success = tree->remove(windowID);
	// if (success) {
	//		TODO: add to map<windowID:set<workspaceID>>
	//		map.erase(windowID);
	// }
	return success;
}