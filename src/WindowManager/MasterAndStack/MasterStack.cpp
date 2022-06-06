#include "MasterStack"

MasterStack::MasterStack(ServerInterfaceArea* server, Area workspaceSize) :
	vertical(true), area(area), numWindws(0), masterSize(width/2), head(nullptr), tail(nullptr){}

void MasterStack::render(ServerInterface* server, MasterStackNode* node, int depth){
	if(node != nullptr){
		if(vertical){
			server->setArea(node->windowID,
			{masterSize,
			depth * (workspaceSize.height / numWindows),
			workspaceSize.width - masterSize,
			(workspaceSize.height / numWindows)});
		} else {
			server->setArea(node->windowID,
			{depth * (workspaceSize.width / numWindows),
			masterSize,
			(workspaceSize.width / numWindows),
			workspaceSize.height - masterSize});
		}
		render(node->next);
	}
}

void MasterStack::render(ServerInterface* server){
	if (head != nullptr){
		if(vertical){
			server->setArea(head->windowID, {0,0, masterSize, workspaceSize.height});
		} else {
			server->setArea(head->windowID, {0,0, workspaceSize.width, masterSize});
		}

		render(server, head->next, 0);
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
		} else { //remove any other node
			while(node->next->windowID != windowID && node->next != nullptr){
				node = node->next;
			}

			if(node->next == nullptr){
				throw string("Unable to remove window with id " + to_string(winodwID) + ".");
			}

			//if node->next is the window to be removed
			if(node->next != nullptr && node->next->windowID == windowID){
				MasterStackNode* tmp = node->next;
				node->next = node->next->next;
				delete tmp;
			}
		}
	}
	numWindows--;
	render(server);
}

void MasterStack::resize(Area area){
	this->area = area;
	render(server);
}
