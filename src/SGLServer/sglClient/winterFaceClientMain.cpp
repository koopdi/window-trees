/**
 * @file winterFaceClientMain.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 * @brief This is the main entry point for the SGL version of WindowTrees
 * @date 06-11-2022
 */

#include <iostream>
#include "Logger.h"
#include "LemonFir.h"
#include "SGLServer.h"
#include "WindowManager.h"

using namespace std;

// Global logger object.
Logger glogger(std::cout, LogLevel::VERBOSE);


int main()
{
		glogger.verb("Creating SGL Server.");
		ServerInterface* server = new SGLServer();

		glogger.verb("Creating Window Manager.");
		WindowManager* winMan   = new WindowManager(server);

		glogger.verb("Registering event handler function.");
		EventHandlerFn evFun    = [&winMan](ev::Event* event) {
      winMan->update(*event);
		};

		glogger.verb("Registering init function.");
		InitHandlerFn initFun = [&winMan](ServerInterface* server) {
			winMan->init();
		};

		server->setInitCallback(initFun);
		server->setEventCallback(evFun);

		glogger.verb("Starting server event loop.");
		server->run();

	return 0;
}