#include "LemonFirNode.h"

const std::string Split::name = "Split";
const std::string Pane::name  = "Pane";

LemonFirNode::LemonFirNode(const std::string& name)
    : type(name) //////////////////////////////////
{
}

Split::Split() : LemonFirNode(name) {}

Pane::Pane() : LemonFirNode(name) {}