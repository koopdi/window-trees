#pragma once

#include <map>

#include "SGLServerWindow.h"

class SGLServerScreen{
    std::map<int, SGLServerWindow> windows;

    SGLServerScreen();
    void addWindow(int windowID);
    void remWindow(int windowID);
};