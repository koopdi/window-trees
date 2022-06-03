#include <iostream>

#include "LemonFir.h"

#include "SGLServer.h"

using namespace std;

int main()
{
	try
	{ // Create an SGL Server for the Window Manager to interface with.
		SGLServer* server     = new SGLServer();
		// Create a Window Manager.
		LemonFir* winMan = new LemonFir(server);

		// Tell the server where to send events.
		EventHandlerFn evFun  = [&winMan](ev::Event* event)
		{ winMan->update(*event); };

		server->setEventCallback(evFun);

		server->run();

	}
	catch (string error)
	{
		cout << error << endl;
	}
	return 0;
}
