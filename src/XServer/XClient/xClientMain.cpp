#include "WindowManager.h"
#include <iostream>
#include "ServerInterface.h"
#include "XServer.h"
#include "LemonFir.h"


#define _DEBUG_PRINT_

int main()
{
	try { // Create an X Server for the Window Manager to interface with.
		ServerInterface* server     = new XServer();
		// Create a Window Manager.
		// WindowManager* winMan = new WindowManager(server);
		LemonFir* winMan = new LemonFir(server);

		// Tell the server where to send events.
		EventHandlerFn evFun  = [&winMan](ev::Event* event) {
      		winMan->update(*event);
		};

		server->setEventCallback(evFun);

		server->run();

	} catch (string error) {
		cout << error << endl;
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