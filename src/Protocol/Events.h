#pragma once

/**
 * @brief This system needs to be implemented.
 * The big idea is that the event struct holds an event type
 * and a union of structs.
 * To find out which struct it is, check the type.
 * The downside of this aproach is that it's not very flexible.
 * Only simple types can be contained in the structs.
 *
 * An alternate method would be to use polymorphism.
 * That would be more flexible and allow complex types like std::string.
 * It would also save more space than the union, as the union
 * has to accomodate the greatest common denominator and can't
 * shrink to fit a type that uses less space.
 *
 * Example usage:
 * ev::Event* ev = new ev::Event;
 * ev->type = ev::EventType::ADD;
 * ev->add.atributeA = 13;
 *
 *
 * Further thoughts:
 * Does it make sense for events to be passed as pointers?
 * Who is responsible for that memory?
 * Would passing them by copy work better?
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

struct Add {
	long winID;
	Area winArea;
};

struct Remove {
	long winID;
};

struct FocusWindow {
	long winID;
};

struct Key {
	long winID;
	bool isUpEv;
	bool isRepeat;
};

struct Mouse {
	int atributeD;
};

struct SwapWindows {
	long winA;
	long winB;
};

enum class Direction { UP, DOWN, LEFT, RIGHT, CENTER };

struct MoveWindow {
	long windowID;
	Direction dir;
};

enum class TreeMode {
	LEMON_FIR,
	BSP_TREE,
	MASTER_STACK,
	HEAP,
	PREV,
	NEXT
}; ////////////////

struct SwitchLayout {
	long screenID;
	TreeMode mode;
};

struct RotateSplit {
	long winID;
};

struct Resize {
	Area size;
};

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

// struct Area
// {
// 	int x;
// 	int y;
// 	int width;
// 	int height;
// };

// typedef unsigned long Window;
// typedef unsigned long Time;

// typedef struct
// {
// 	int type;
// 	Window parent; /* parent of the window */
// 	Window window; /* window id of window created */
// 	Area windowArea;
// 	int border_width; /* border width */
// } CreateWindowEvent;

// typedef struct
// {
// 	int type;
// 	Window event;
// 	Window window;
// } DestroyWindowEvent;

// typedef struct
// {
// 	int type; /* of event */
// 	// Window windownamespace ev;
// 	/* "event" window it is reported relative to */
// 	Window root;          /* root window that the event occurred on */
// 	Window subwindow;     /* child window */
// 	Time time;            /* milliseconds */
// 	int x, y;             /* pointer x, y coordinates in event window */
// 	int root_x, root_y;   /* coordinates relative to root */
// 	unsigned int state;   /* key or button mask */
// 	unsigned int keycode; /* detail */
// } KeyEvent;

// union Event
// {
// 	int type;
// 	CreateWindowEvent create;
// 	DestroyWindowEvent destroy;
// 	KeyEvent keyEvent;
// };

} // namespace ev