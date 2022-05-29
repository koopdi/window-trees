#include "types.h"

struct ServerWindowSDL
{
	long windowID;
	int depth;
	Area area;

	bool operator==(ServerWindowSDL& win2);
	bool operator<(ServerWindowSDL& win2);
};