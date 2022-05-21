#include <iostream>
#include "WindowManager.h"
#include "DisplayServer.h"
#include "ServerInterface.h"
#include "XServer.h"

int main(){
////********************************************************
	#ifdef _WIN32
	ServerInterface* server = new DisplayServer();
	/*
	struct foo{
		void run() {};
	};
	foo blah;
	ServerInterface* server = (ServerInterface*)(&blah);
	*/
	WindowManager windowManager(server);
////********************************************************
	#else
	ServerInterface* server = new XServer();
	WindowManager windowManager(server);
	#endif


	server->run();
	return(0);
}