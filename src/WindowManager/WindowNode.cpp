
#include "WindowNode.h"

bool WindowPane::hasTag(int tag) {return 0;}
bool WindowPane::addTag(int tag) {return 0;}
bool WindowPane::removeTag(int tag) {return 0;}

WindowNode::WindowNode(bool partVertically, int windowID, double part1Size)
	: partVertically(partVertically), windowID(windowID), part1Size(part1Size) {}

WindowNode::WindowNode() {}
