#include "BSPTree.h"

void Workspace::render(WindowNode* node, Area bounds){
	if(node != nullptr){
		if(node->isWindow()){										//node->isWindow() appears to be non functional
			server->setArea(node->window->windowID, bounds);
		} else {
			if(node->partVertically){
				bounds.height -= node->part1Size; //restrict area to bottom size
				bounds.y += node->part1Size; //select bottom area
				renderTree(node->part2, bounds); //render bottom area

				bounds.height = node->part1Size;
				bounds.y -= node->part1Size;
				renderTree(node->part1, bounds); //render top section
			} else {
				bounds.width -= node->part1Size; //restrict area to right size
				bounds.x += node->part1Size; //select right area
				renderTree(node->part2, bounds); //render right area

				bounds.width = node->part1Size;
				bounds.x -= node->part1Size;
				renderTree(node->part1, bounds); //render left section
			}
		}
	}
}

void BSPTree::addWindow(long windowID){

}

void BSPTree::remWindow(long windowID){

}
