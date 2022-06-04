#include "BSPNode.h"

BSPNode::BSPNode(bool partVertically, int windowID, short part1PerPrecision) :
partVertically(partVertically), windowID(windowID), part1(nullptr), part2(nullptr),
part1PerPrecision(part1PerPrecision) {}

BSPNode::~BSPNode(){
	delete part1;
	delete part2;
	delete this;
}

bool BSPNode::isWindow(){
	return windowID == -1;
}