#include "WM.h"
#include <string>

using namespace std;

WM::WM(ServerInterface* server)
{
	if (server == nullptr)
	{
		throw "Failed to initialize Workspace Manager: "
		      "Provided server is null.";
	}
}