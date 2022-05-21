#include <map>

#include "DisplayServerWindow.h"

class DisplayServerScreen{
    std::map<int, DisplayServerWindow> windows;

    DisplayServerScreen();
    void addWindow(int windowID);
    void remWindow(int windowID);
};