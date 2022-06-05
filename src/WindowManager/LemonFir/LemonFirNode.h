#pragma once

#include <string>
#include <memory>

#include "types.h"

struct LemonFirNode;
using nodePtr = std::shared_ptr<LemonFirNode>;

struct LemonFirNode {
	/// A tag to make runtime type inference easy.
	const std::string_view& type;
	virtual ~LemonFirNode();

protected:
	/// This constructor must be called from the derived class.
	/// \param name The name of the derived class.
	/// \note Name must exist for the lifetime of this object.
	LemonFirNode(const std::string_view& name);
};

/// A parent node.
struct Split : public LemonFirNode {
	/// Create a split node.
	Split();

	/// True when split is left|right,
	/// False when split is top/bottom.
	bool vSplit;

	/// The top/left child.
	nodePtr left;

	/// The bottom/right child.
	nodePtr right;

private:
	/// A tag to make runtime type inference easy.
	OMEGA_CONST name = std::string_view("Split");
};

/// A leaf node.
struct Pane : public LemonFirNode {
	/// Create a leaf node.
	Pane(long windowID);

	const long windowID;

private:
	/// A tag to make runtime type inference easy.
	OMEGA_CONST name = std::string_view("Pane");
};

// enum NodeType
// {
// 	NODE,
// 	PANE
// };
// static const NodeType type;
