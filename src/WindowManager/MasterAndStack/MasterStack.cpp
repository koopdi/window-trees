#include "MasterStack.h"
#include <cmath>


void MasterStack::swapWindows(long windowA, long windowB){

}


MasterStack::MasterStack(ServerInterface* server, Area area) : server(server), area(area),
	vertical(true), numWindows(0), masterSize(area.width/2), head(nullptr), tail(nullptr){}

void MasterStack::render(MasterStackNode* node, int cumOffset, int depth){
	if(node != nullptr){
		double rem = 0;
		int stackedWindows = numWindows - 1;

		if(vertical){
			rem = ceil(1.0 * area.height / stackedWindows) - (int)(area.height / stackedWindows);
			server->setArea(node->windowID,
				{masterSize,
				depth * (area.height / stackedWindows) + cumOffset,
				area.width - masterSize,
				(int)((area.height / stackedWindows) + rem)}
			);
		} else {
			rem = ceil(1.0 * area.width / stackedWindows) - (int)(area.width / stackedWindows);
			server->setArea(node->windowID,
				{depth * (area.width / stackedWindows) + cumOffset,
				masterSize,
				(int)((area.width / stackedWindows) + rem),
				area.height - masterSize}
			);
		}
		cumOffset += rem;
		render(node->next, cumOffset, depth + 1);
	}
}

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

void MasterStack::resize(Area area){
	this->area = area;
}

void MasterStack::rotateSplit(long windowID){
	vertical = !vertical;
	if(vertical){
		masterSize = area.width/2;
	} else {
		masterSize = area.height/2;
	}
}
