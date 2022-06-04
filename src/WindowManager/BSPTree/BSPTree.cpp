#include "BSPTree.h"

BSPTree::BSPTree(){
	root = new BSPNode(true, -1, 100);
}

void Workspace::render(BSPNode* node, Area bounds){
	if(node != nullptr){
		if(node->isWindow()){
			Area precision = {node->precision, node->precision, node->precision, node->precision};
			server->setArea(node->window->windowID, (float)bounds / precision * area);
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

void insertWin(BSPNode*& node, BSPNode* newNode){
	if(node == nullptr){
		throw string("A new node may not be inserted onto nullptr");
	} else {
		if(node->isWindow()){
			BSPNode* tmp = node;
			node = new BSPNode(!node->partVertically, -1, node->part1 / 2);
			node->part1 = tmp;
			node->part2 = newNode;
		} else {
			node
		}

		if(node->part1 == nullptr + node->part2 == nullptr == 1){
			if(node->part1 == nullptr){

			}
		}
	}
}

void BSPTree::addWindow(long windowID, WindowNode*& node){
	if(node->left == nullptr && node){
		WindowNode* tmp = node;

	} else {
		addWindow(windowID, node->right);
	}
}

void BSPTree::addWindow(long windowID){
	addWindow(windowID, root);
}

void BSPTree::remWindow(long windowID){

}

void resize(Area area) {
	this->area = area;
	std::cout << "recursively resize workspaces here" << std::endl;
}
