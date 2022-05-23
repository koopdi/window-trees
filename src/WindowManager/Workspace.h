#include "WindowNode.h"
#include "types.h"
#include "WindowTree.h"

class Workspace {
public:
    Workspace(int workspaceID);
    int getHeight() const;
    int getWidth() const;
    Point getPosition() const;
    int getNumWindows() const;

private:
    WindowTree* tree;
    int height;
    int width;
    int numWindows;
    Point position;

    void setHeight(int height);
    void setWidth(int width);
    void setPosition(Point position);
    bool addWindow(bool partVertically, int windowID, double part1Size);
    bool removeWindow(int windowID);
};