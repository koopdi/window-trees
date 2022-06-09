#include "WindowManager.h"
#include <iostream>
#include "ServerInterface.h"
#include "XServer.h"


#define _DEBUG_PRINT_

int main()
{
	try { // Create an X Server for the Window Manager to interface with.
		ServerInterface* server     = new XServer();
		// Create a Window Manager.
		// WindowManager* winMan = new WindowManager(server);
		WindowManager* winMan = new WindowManager(server);

		// Tell the server where to send events.
		EventHandlerFn evFun  = [&winMan](ev::Event* event) {
      		winMan->update(*event);
		};

		InitHandlerFn initFun = [&winMan](ServerInterface* server) {
      		winMan->init();
		};

		server->setInitCallback(initFun);
		server->setEventCallback(evFun);

		server->run();

	} catch (std::string error) {
		std::cout << error << std::endl;
	}


// #ifdef _DEBUG_PRINT_
// 	std::cout << "new windowManager()" << std::endl;
// #endif

// 	ServerInterface* server = new XServer();
// 	WindowManager winMan(server);

// #ifdef _DEBUG_PRINT_
// 	std::cout << "run" << std::endl;
// #endif

// 	EventHandlerFn handlerFunc = [&winMan](ev::Event* event)
// 	{ winMan.update(*event); };

// 	server->setEventCallback(handlerFunc);

// 	server->run();

// #ifdef _DEBUG_PRINT_
// 	std::cout << "return(0)" << std::endl;
// #endif
}