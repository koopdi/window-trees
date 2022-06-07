#include "MasterStack.h"

MasterStack::MasterStack(ServerInterface* server, Area area) : vertical(true), area(area),
	numWindows(0), masterSize(area.width/2), head(nullptr), tail(nullptr){}

void MasterStack::render(MasterStackNode* node, int depth){
	if(node != nullptr){
		if(vertical){
			server->setArea(node->windowID,
			{masterSize,
			depth * (area.height / numWindows),
			area.width - masterSize,
			(area.height / numWindows)});
		} else {
			server->setArea(node->windowID,
			{depth * (area.width / numWindows),
			masterSize,
			(area.width / numWindows),
			area.height - masterSize});
		}
		render(node->next, depth + 1);
	}
}

void MasterStack::render(ServerInterface* server){
	if (head != nullptr){
		if(vertical){
			server->setArea(head->windowID, {0,0, masterSize, area.height});
		} else {
			server->setArea(head->windowID, {0,0, area.width, masterSize});
		}

		render(head->next, 0);
	}
}

void MasterStack::addWindow(long windowID){
	numWindows++;
	if(head == nullptr){
		head = new MasterStackNode(windowID, nullptr);
		tail = head;
	} else {
		tail->next = new MasterStackNode(windowID, nullptr);
		tail = tail->next;
	}
	render(server);
}

void MasterStack::remWindow(long windowID){
	MasterStackNode* node = head;
	if(node != nullptr){
		if(node->windowID == windowID){ //remove head
			delete head;
			head = nullptr;
			tail = nullptr;
		} else { //remove any other node
			while(node->next->windowID != windowID && node->next != nullptr){
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
	render(server);
}

void MasterStack::resize(Area area){
	this->area = area;
	render(server);
}
