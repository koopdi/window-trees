namespace ev
{

struct Area
{
	int x;
	int y;
	int width;
	int height;
};

typedef unsigned long Window;
typedef unsigned long Time;

typedef struct
{
	int type;
	Window parent; /* parent of the window */
	Window window; /* window id of window created */
	Area windowArea;
	int border_width; /* border width */
} CreateWindowEvent;

typedef struct
{
	int type;
	Window event;
	Window window;
} DestroyWindowEvent;

typedef struct
{
	int type; /* of event */
	// Window windownamespace ev;
  /* "event" window it is reported relative to */
	Window root;          /* root window that the event occurred on */
	Window subwindow;     /* child window */
	Time time;            /* milliseconds */
	int x, y;             /* pointer x, y coordinates in event window */
	int root_x, root_y;   /* coordinates relative to root */
	unsigned int state;   /* key or button mask */
	unsigned int keycode; /* detail */
} KeyEvent;

union Event
{
	int type;
	CreateWindowEvent create;
	DestroyWindowEvent destroy;
	KeyEvent keyEvent;
};

} // namespace ev