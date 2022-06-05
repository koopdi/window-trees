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