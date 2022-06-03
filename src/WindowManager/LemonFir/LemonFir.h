#pragma once

/***********************************************************
 * Class Lemon Fir
 * The growth tips taste like lemon.
 * *********************************************************
 * @file LemonFir.h
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */

#include "ServerInterface.h"

// #include "WindowManager.h"

class LemonFir //: public WindowManager
{
public:
	LemonFir(ServerInterface* server);

	void update(ev::Event& ev);

private:
	/// A pointer to the server.
	ServerInterface* server;
};