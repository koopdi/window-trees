#include "WMWorkspace.h"
#include "xtypes.h"
#include "ServerInterface.h"

class WM {
    vector<WMWorkspace> workspaces;
    void update(XEvent& ev);
public:
    WM(ServerInterface* server);
};