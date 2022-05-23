/**
 * @file WindowManager.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <string>

#include "WindowManager.h"

using namespace std;

/**
 * @brief Construct a new Window Manager:: Window Manager object
 *
 * @param server
 */
WindowManager::WindowManager(ServerInterface* server)
{
	if (server == nullptr)
	{
		throw "Failed to initialize Workspace Manager: "
		      "Provided server is null.";
	}
}