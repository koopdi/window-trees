#include <iostream>
#include "WindowManager.h"
#include "ServerInterface.h"
#include "DisplayServerSDL.h"

int main(){
	ServerInterface* server = new DisplayServerSDL();
	WindowManager wm(server);

	server->run();
}