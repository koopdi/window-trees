/***********************************************************
 * This is the main entry point to test WindowTrees using SGL
 * as a server backend and as a system layer that forwards
 * mouse and keeb inputs to the event system of said server.
 *
 * @file sglClientMain.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 * @brief An interactive graphics environment to test Windowing.
 * @date 6/10/2022
 */

#include <iostream>

#include "SGLServer.h"

#include "WindowManager.h"

// using namespace std;
// using namespace sgl;

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
	try
	{ // Create an SGL Server for the Window Manager to interface with.
		SGLServer* server     = new SGLServer();
		// Create a Window Manager.
		WindowManager* winMan = new WindowManager(server);

		// Tell the server where to send events.
		EventHandlerFn evFun  = [&winMan](ev::Event* event)
		{ winMan->update(*event); };

		server->setEventCallback(evFun);

	}
	catch (string error)
	{
		cout << error << endl;
	}
	return 0;
}
