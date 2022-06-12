#include "Workspace.h"
/** @file Workspace.cpp
 * @brief provides implementations for the methods defined in Workspace.h
 * @author Christen Spadavecchia
 * @date 6/10/2022
 * CS 133
*/
#include <iostream>

/** @brief creates a Workspace (layout manager)
 * @param server A ServerInterface pointer used by layouts (classes extending WindowTreeInterface)
 * @param screenID the ID of the screen that the workspace was created on
*/
Workspace::Workspace(ServerInterface* server, long screenID)
    : server(server), treeLayoutMode(ev::TreeMode::LEMON_FIR)
{
	Area screenSize                         = server->getScreenSize(screenID);

	windowTrees[ev::TreeMode::LEMON_FIR]    = new LemonFir(server);
	windowTrees[ev::TreeMode::MASTER_STACK] = new MasterStack(server, screenSize);
	// windowTrees[ev::TreeMode::HEAP] = new HeapTree(server); //currently unstable
}

/** @brief renders the active layout by calling the layout specific render function */
void Workspace::render() { windowTrees.at(treeLayoutMode)->render(server); }

/** @brief Adds a window to the workspace
 * @param windowID the id of the window being added
 */
void Workspace::addWindow(long windowID)
{
	for (auto [LAYOUT_MODE, layoutPtr] : windowTrees) {
		// std::cout << "WorkSpace addWindow: " << std::endl;
		layoutPtr->addWindow(windowID);
	}
}

/** @brief removes a window from the workspace
 * @param windowID the window to be removed
*/
void Workspace::remWindow(long windowID)
{
	for (auto [LAYOUT_MODE, layoutPtr] : windowTrees) {
		// std::cout << "WorkSpace remWindow: " << std::endl;
		layoutPtr->remWindow(windowID);
	}
}

/** @brief rotates the split direction for a given window in the workspace
 * @param windowID the id of the window being "rotated"
 */
void Workspace::rotateSplit(long windowID)
{
	windowTrees.at(treeLayoutMode)->rotateSplit(windowID);
}

/** @brief resizes the workspace
 * @param area the new area of the workspace
 */
void Workspace::resize(Area area)
{
	for (std::pair<ev::TreeMode, WindowTreeInterface*> pair : windowTrees) {
		pair.second->resize(area);
	}
}

/** @brief swaps the layout position of 2 windows in the workspace
 * @param windowA first window to be swapped
 * @param windowB second window to be swapped
*/

void Workspace::swapWindows(long windowA, long windowB)
{
	windowTrees.at(treeLayoutMode)->swapWindows(windowA, windowB);
}

/** @brief sets the layout mode for the workspace
 * @param mode a TreeMode that determines the layout mode, may any type in the TreeMode enum
 */
void Workspace::setLayoutMode(ev::TreeMode mode)
{
	std::string treeName;
	if ((int)treeLayoutMode == 0) treeName = "LEMON_FIR";
	if ((int)treeLayoutMode == 2) treeName = "MASTER_STACK";
	if ((int)treeLayoutMode == 3) treeName = "HEAP";

	using std::cout;
	using std::endl;
	std::cout << "setLayoutMode, mode = " << std::oct << (int)mode << std::endl;
	if (mode == ev::TreeMode::PREV) {
		cout << "mode: PREV	#" << (int)mode << endl;
		std::vector<ev::TreeMode> modes = getAvailableModes();
		cout << "Number of available modes: " << modes.size() << endl;
		if (modes.size() > 1) {
			for (int i = 0; i < modes.size() - 1; i++) {
				if (modes[i + 1] == treeLayoutMode) {
					treeLayoutMode = modes[i];
				}
			}
		}

	} else if (mode == ev::TreeMode::NEXT) {
		cout << "mode: NEXT	#" << (int)mode << endl;
		auto iter = windowTrees.find(mode);
		int count = windowTrees.size();
		cout << "Number of available modes: " << count << endl;
		cout << "Current mode: #" << treeName << endl;

		auto currLayout = windowTrees.find(treeLayoutMode);
		currLayout++;
		if (currLayout == windowTrees.end()) {
			currLayout = windowTrees.begin();
		}
		treeLayoutMode = currLayout->first;
	} else {
		treeLayoutMode = mode;
	}
}

/** @brief returns the available layout modes for the workspace*/
std::vector<ev::TreeMode> Workspace::getAvailableModes()
{
	std::vector<ev::TreeMode> modes;
	for (auto [mode, ptr] : windowTrees) {
		modes.push_back(mode);
	}
	return modes;
}

/** @brief returns the active layout mode for a workspace */
ev::TreeMode Workspace::getActiveMode() { return treeLayoutMode; }