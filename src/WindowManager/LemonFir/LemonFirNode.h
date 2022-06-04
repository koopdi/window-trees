#pragma once

#include <string>

struct LemonFirNode {
	/// A tag to make runtime type inference easy.
	const std::string& type;

protected:
	/// This constructor must be called from the derived class.
	/// \param name The name of the derived class.
	/// \note The name should exist for the lifetime of the class.
	LemonFirNode(const std::string& name);
};

struct Split : public LemonFirNode {
	Split();

private:
	/// A tag to make runtime type inference easy.
	static const std::string name;
};

struct Pane : public LemonFirNode {
	Pane();

private:
	/// A tag to make runtime type inference easy.
	static const std::string name;
};

// enum NodeType
// {
// 	NODE,
// 	PANE
// };
// static const NodeType type;
