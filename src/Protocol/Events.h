#pragma once

/**
 * @file Events.h
 * @author Christen Spadevechia, Travis McKinney
 * @date 6/10/22
 * @brief
 * The big idea is that the event struct holds an event type
 * and a union of structs.
 * To find out which struct it is, check the type.
 *
 */

#include "types.h"
namespace ev
{
// The type of event.
enum class EventType {
	ADD,           // Add a window.
	REMOVE,        // Remove a window
	FOCUS,         // A window was focused.
	KEY,           // A key was pressed
	MOUSE,         // A mouse was moved
	SWAP_WINDOWS,  // Swap window placement.
	MOVE_WINDOW,   // Move window request
	SWITCH_LAYOUT, // Layout switch request
	RESIZE,        // The screen was resized.
	ROTATE_SPLIT,  // Rotate the split orientation
	OTHER,         // Backend specific
	GARBAGE        // Unhandled
};

//add event specific fields
struct Add {
	long winID;
	Area winArea;
};

//remove event specific fields
struct Remove {
	long winID;
};

//focus event specific fields
struct FocusWindow {
	long winID;
};

//key event specific fields
struct Key {
	long winID;
	bool isUpEv;
	bool isRepeat;
};

//mouse event specific fields
struct Mouse {
	int atributeD;
};

//window swap event specific fields
struct SwapWindows {
	long winA;
	long winB;
};

//enum for the 4 cardinal directions and center (up, down, left, right, center)
enum class Direction { //
	UP,
	DOWN,
	LEFT,
	RIGHT,
	CENTER
};

//movewindow event specific fields
struct MoveWindow {
	long windowID;
	Direction dir;
};

//enum for every tree available as a layout to workspaces (and prev/next)
enum class TreeMode {
	LEMON_FIR,
	BSP_TREE,
	MASTER_STACK,
	HEAP,
	PREV,
	NEXT
};

//layout switch event specific fields
struct SwitchLayout {
	long screenID;
	TreeMode mode;
};

//split direction change event specific fields
struct RotateSplit {
	long winID;
};

//workspace resize event specific fields
struct Resize {
	Area size;
};

//Unified window manager event type
struct Event {
	EventType type;
	long screenID;
	union {
		Add add;
		Remove remove;
		FocusWindow focus;
		Key key;
		Mouse mouse;
		SwapWindows swap;
		MoveWindow move;
		SwitchLayout layout;
		RotateSplit rotate;
		Resize resize;
	};
};
} // namespace ev