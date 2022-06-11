#pragma once

/**
 * @file WindowNode.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */

#include "types.h"

struct HeapWindow{
	int windowID;
	bool partVertically;
	int part1Size;
	Area area;
	HeapWindow* left;
	HeapWindow* right;

	HeapWindow(int WindowID, Area area);
	HeapWindow
	(
		bool partVertically,
		int part1Size,
		HeapWindow* left = 0,
		HeapWindow* right = 0
	);

	bool isWindow() const;
};