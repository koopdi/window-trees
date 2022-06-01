#include "ServerInterface.h"
#include "types.h"
#include <set>
class TermServer : public ServerInterface{
	std::set<Area> windows;
	TermServer();

};