#include "DisplayServerWindow.h"

class DisplayServerScreen{
    map<int, DisplayServerWindow> windows;

    DisplayServerScreen();
    void addWindow(int windowID);
    void remWindow(int windowID);
};