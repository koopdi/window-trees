#include "LemonFirNode.h"

#include <iostream>
using std::cout;
using std::endl;

// const std::string Split::name = "Split";
// const std::string Pane::name  = "Pane";

LemonFirNode::LemonFirNode(const std::string_view& name)
    : type(name) ///////////////////////////////////////////
{
}

LemonFirNode::~LemonFirNode() {}

// Split* LemonFirNode::getSplit()
// {
// 	return std::dynamic_cast<Split*>(this);
// }

// LemonFirNode::getPane(){
// 	return std::dynamic_pointer_cast<Pane*>
// }

Split::Split() : LemonFirNode(name), vSplit(true) ////////////////////////
{
}

Pane::Pane(long windowID)
    : windowID(windowID), LemonFirNode(name) ///////////////
{
}

/// Get pointer to the stored split object.
Split* getSplit(NodePtr node) { return dynamic_cast<Split*>(node.get()); }

/// Get a pointer to the stored Pane object.
Pane* getPane(NodePtr node) { return dynamic_cast<Pane*>(node.get()); }

/// Get pointer to the stored split object.
Split* getSplit(NodePtr* node)
{
	if (node) {
		return dynamic_cast<Split*>(node->get());
	} else {
		return nullptr;
	}
}

/// Get a pointer to the stored Pane object.
Pane* getPane(NodePtr* node)
{
	if (node) {
		// cout << "(*node).unique:" << std::boolalpha << (*node).unique() << endl;
		return dynamic_cast<Pane*>(node->get());
	} else {
		return nullptr;
	}
}