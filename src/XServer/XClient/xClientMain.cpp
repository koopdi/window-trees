#include <iostream>
#include "WindowManager.h"
// #include "DisplayServer.h"
#include "ServerInterface.h"
#ifdef HAS_XLIB
#include "XServer.h"
#endif
#define _DEBUG_PRINT_

int main(){
////********************************************************
	#ifndef HAS_XLIB
	#ifdef _DEBUG_PRINT_
	std::cout << "new" << std::endl;
	#endif
	// ServerInterface* server = new DisplayServer();
	/*
	struct foo{
		void run() {};
	};
	foo blah;
	ServerInterface* server = (ServerInterface*)(&blah);
	*/
	#ifdef _DEBUG_PRINT_
	std::cout << "windowManager()" << std::endl;
	#endif
	// WindowManager windowManager(server);
////********************************************************
	#else
	ServerInterface* server = new XServer();
	WindowManager windowManager(server);
	#endif

	#ifdef _DEBUG_PRINT_
	std::cout << "run" << std::endl;
	#endif

	// server->run();

	#ifdef _DEBUG_PRINT_
	std::cout << "return(0)" << std::endl;
	#endif

	#ifdef HAS_XLIB
	return(1);
	#else
	return(1);
	exit(1);
	#endif
}