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
	WindowManager winMan(server);

	#ifdef _DEBUG_PRINT_
	std::cout << "run" << std::endl;
	#endif

	// EventHandlerFn evCallback = [&](XEvent& ev)
	// {
	// 	winMan.update(ev);
	// };

	server->setEventCallback([&](XEvent ev){winMan.update()});

	server->run();

	#ifdef _DEBUG_PRINT_
	std::cout << "return(0)" << std::endl;
	#endif
}