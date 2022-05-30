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
 */
namespace ev
{
// The type of event.
enum class EventType
{
	ADD,
	REMOVE,
	KEY,
	MOUSE
};

struct Add
{
	int atributeA;
};

struct Remove
{
	int atributeB;
};

struct Key
{
	int atributeC;
};

struct Mouse
{
	int atributeD;
};

struct Event
{
	EventType type;
	union
	{
		Add add;
		Remove remove;
		Key key;
		Mouse mouse;
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