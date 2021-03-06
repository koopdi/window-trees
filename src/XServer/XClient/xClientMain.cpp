#include "WindowManager.h"
#include <iostream>
#include "ServerInterface.h"
#include "XServer.h"

/** @brief
 * Main for the X Server window manager backend
 * Creates an "XServer" and a WindowManager, and sets up event callbacks, and starts the event loop
*/
		Logger glogger(std::cout, LogLevel::VERBOSE);


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