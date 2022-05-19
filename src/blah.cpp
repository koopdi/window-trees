#include <vector>
#include <string>
#include <map>

using namespace std;

typedef struct Point{
    int x;
    int y;
} Point;

struct QuadNode{};

class QuadTree{
public:
    QuadTree();

    void remove(Window* window);
    void add(Window* window);
    void print();
    void printSideways();
    bool contains(Window* window);

private:
    Window* window;
    QuadNode* northWest;
    QuadNode* northEast;
    QuadNode* southWest;
    QuadNode* southEast;

    void printSidewaysHelper(QuadNode* node, string spaces);
};

int main(){
    DisplayManager display;
    WorkspaceManager* manager =  display.getManager();
}

class DisplayManager{
public:
    DisplayManager();
    WorkspaceManager* getManager();

private:
    WorkspaceManager*  createManager();
    WorkspaceManager* manager;
};

class ServerInterface{
public:
    void draw(DisplayManager*);
private:
    DisplayManager* gui;
};

class WorkspaceManager {
public:
    WorkspaceManager(ServerInterface* interface);
    Workspace* createWorkspace(int height = 0, int width = 0, Point position = Point{0, 0});
    int getNumWorkspaces();

private:
    void removeWindow(Window*);
    int numWorkspaces;
    vector<Workspace*> workspaces;
    ServerInterface* interface;
};


class Window {
public:
    Window(int height = 0, int width = 0, Point position = Point{0, 0});
    int getHeight() const;
    int getWidth() const;
    int getPosition() const;

private:
    int height;
    int width;
    Point position;
    vector<Workspace*> tags;

    void setHeight(int height);
    void setWidth(int width);
    void setPosition(Point position);
};

class Workspace {
public:
    Workspace(int height = 0, int width = 0, Point position = Point{0, 0});
    int getHeight() const;
    int getWidth() const;
    int getPosition() const;
    int getNumWindows() const;

private:
    map<int, Window*> WindowIDs;
    vector<Window*> Windows;
    QuadTree tiles;
    int height;
    int width;
    int numWindows;
    Point position;

    void setHeight(int height);
    void setWidth(int width);
    void setPosition(Point position);
    Window* createWindow(int height = 0, int width = 0, Point position = Point{0, 0});
    void removeWindow(Window*);
};

class WorkspaceManager {
public:
    WorkspaceManager(ServerInterface* interface);
    Workspace* createWorkspace(int height = 0, int width = 0, Point position = Point{0, 0});
    int getNumWorkspaces();

private:
    void removeWindow(Window*);
    int numWorkspaces;
    vector<Workspace*> workspaces;
    ServerInterface* interface;
};
