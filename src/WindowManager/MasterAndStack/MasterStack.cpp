#include "MasterStack.h"

/** @file MasterStack.cpp
 * Provides implementations for the methods defined in MasterStack.h
 * @author Christen Spadavecchia
 * @date Spring 2022
 * CS 133
*/

/// @brief swaps the id of 2 MasterStackNodes by windowID
void MasterStack::swapWindows(long windowA, long windowB){

}

/// @brief ctor for MasterStack, takes a ServerInterface* and an area
MasterStack::MasterStack(ServerInterface* server, Area area) : server(server), area(area),
	vertical(true), numWindows(0), masterSize(area.width/2), head(nullptr), tail(nullptr){}

/// @brief renders a linked list of MasterStackNodes by calling server->setArea on each node
/// uses cumOffset (cumulative offset) and a depth int
void MasterStack::render(MasterStackNode* node, int cumOffset, int depth){
	if(node != nullptr){
		double rem = 0;
		int stackedWindows = numWindows - 1;

		//set window area
		if(vertical){
			rem = ceil(1.0 * area.height / stackedWindows) - (int)(area.height / stackedWindows);
			server->setArea(node->windowID,
				{masterSize,//x
				depth * (area.height / stackedWindows) + cumOffset,//y
				area.width - masterSize,//w
				(int)((area.height / stackedWindows) + rem)}//h
			);
		} else {
			rem = ceil(1.0 * area.width / stackedWindows) - (int)(area.width / stackedWindows);
			server->setArea(node->windowID,
				{depth * (area.width / stackedWindows) + cumOffset,//x
				masterSize,//y
				(int)((area.width / stackedWindows) + rem),//w
				area.height - masterSize}//h
			);
		}
		cumOffset += rem; //add offset for placement of next window
		render(node->next, cumOffset, depth + 1);//render next node
	}
}

/// @brief implements the render method as defiend by the WindowTreeInterface
void MasterStack::render(ServerInterface* server){
	if (head != nullptr){
		if(numWindows == 1){
			server->setArea(head->windowID, {0,0, area.width, area.height});
		} else {
			if(vertical){
				server->setArea(head->windowID, {0,0, masterSize, area.height});
			} else {
				server->setArea(head->windowID, {0,0, area.width, masterSize});
			}
		}

		render(head->next, 0, 0);
	}
}

/// @brief implements the addWindow method defined by the WindowTreeInterface
/// adds the given windowID to the linkedlist and updates the tail ptr
void MasterStack::addWindow(long windowID){
	if(head == nullptr){
		head = new MasterStackNode(windowID, nullptr);
		tail = head;
	} else {
		tail->next = new MasterStackNode(windowID, nullptr);
		tail = tail->next;
	}
	numWindows++;
}

/// @brief implements the remWindow method defined by the WindowTreeInterface
/// updates the head and tail pointers a necessary
void MasterStack::remWindow(long windowID){
	MasterStackNode* node = head;
	if(node != nullptr){
		if(node->windowID == windowID){ //remove head
			head = head->next;
			delete node;
			if(numWindows == 0){
				tail = nullptr;
			}
		} else { //remove any other node
			while(node->next != nullptr && node->next->windowID != windowID){
				node = node->next;
			}

			if(node->next == nullptr){
				throw std::string("Unable to remove non-existant window with id "
					+ std::to_string(windowID));
			}

			//if node->next is the window to be removed (node->next->windowID == windowID)
			MasterStackNode* tmp = node->next;
			node->next = node->next->next;
			delete tmp;
			tail = node;
		}
	}
	numWindows--;
}

/// @brief implements resize as defined by WindowTreeInterface (sets new area)
void MasterStack::resize(Area area){
	this->area = area;
}

///@brief implements resize as defined by WindowTreeInterface
///(changes the rotation direction of the entire layout instead of on a per window basis)
void MasterStack::rotateSplit(long windowID){
	vertical = !vertical;
	if(vertical){
		masterSize = area.width/2;
	} else {
		masterSize = area.height/2;
	}
}
