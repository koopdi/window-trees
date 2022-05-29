#include "ServerWindowSDL.h"

bool ServerWindowSDL::operator==(ServerWindowSDL& win2){
	return depth == win2.depth;
}

bool ServerWindowSDL::operator<(ServerWindowSDL& win2){
	return depth < win2.depth;
}
