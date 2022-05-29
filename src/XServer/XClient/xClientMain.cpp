#include <iostream>
#include "WindowManager.h"
// #include "DisplayServer.h"
#include "ServerInterface.h"
#include "XServer.h"

#define _DEBUG_PRINT_

int main(){
	#ifdef _DEBUG_PRINT_
	std::cout << "new windowManager()" << std::endl;
	#endif

	ServerInterface* server = new XServer();
	WindowManager windowManager(server);

	#ifdef _DEBUG_PRINT_
	std::cout << "run" << std::endl;
	#endif

	server->run();

	#ifdef _DEBUG_PRINT_
	std::cout << "return(0)" << std::endl;
	#endif
}