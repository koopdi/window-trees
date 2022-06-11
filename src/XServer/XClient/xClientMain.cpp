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

		// Tell the server what function to call on initialization
		InitHandlerFn initFun = [&winMan](ServerInterface* server) {
      		winMan->init();
		};

		//actually set init and event callbacks
		server->setInitCallback(initFun);
		server->setEventCallback(evFun);

		// Start the X Server Backend event loop
		server->run();

	} catch (std::string error) {
		std::cout << error << std::endl;
	}
}