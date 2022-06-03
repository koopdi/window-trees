#include "BSPNode.h"

BSPNode::BSPNode(bool partVertically, int windowID) : partVertically(partVertically),
	windowID(windowID), part1(nullptr), part2(nullptr), part1Size(200) {}

BSPNode::~BSPNode(){
	delete part1;
	delete part2;
	delete this;
}

bool BSPNode::isWindow(){
	return windowID == -1;
}