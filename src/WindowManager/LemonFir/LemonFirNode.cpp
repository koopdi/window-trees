#include "LemonFirNode.h"

// const std::string Split::name = "Split";
// const std::string Pane::name  = "Pane";

LemonFirNode::LemonFirNode(const std::string_view& name)
    : type(name) ///////////////////////////////////////////
{
}

LemonFirNode::~LemonFirNode(){}

Split::Split() : LemonFirNode(name) ////////////////////////
{
}

Pane::Pane(long windowID)
    : windowID(windowID), LemonFirNode(name) ///////////////
{
}

/// Get pointer to the stored split object.
Split* getSplit(NodePtr node)
{
	return dynamic_cast<Split*>(node.get());
}

/// Get a pointer to the stored Pane object.
Pane* getPane(NodePtr node)
{
	return dynamic_cast<Pane*>(node.get());
}
