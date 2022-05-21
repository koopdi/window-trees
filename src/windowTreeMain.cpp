#include <iostream>
#include "WindowManager.h"
#include "XServer.h"
#include "ServerInterface.h"

int main(){
	ServerInterface* server = new XServer();
	WindowManager windowManager(server);
	server->run();
	return(0);
}