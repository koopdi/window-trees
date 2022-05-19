#include <vector>
#include <string>
#include <map>
#include <unordered_set>

using namespace std;

typedef struct Point{
    int x;
    int y;
} Point;

class DisplayServerWindow {
public:
    DisplayServerWindow(int height = 0, int width = 0,
        Point position = Point{0, 0}, bool partVertically = true);
    int getHeight() const;
    int getWidth() const;
    int getPosition() const;
    int getID() const;
    void setHeight(int height);
    void setWidth(int width);
    void setPosition(Point position);

private:
    static int idTicker;
    sgl::GObject* gobj;
    int height;
    int width;
    int windowID;
    Point position;
};

enum EventType{
    ADD_WINDOW,
    REMOVE_WINDOW,
    MOVE_WINDOW,
    LDOWN,
    LUP,
    RDOWN,
    RUP,
};

struct DisplayServerEvent{
    EventType type;
    int windowID;
    int screenID;
    Point pos;
};

class DisplayServerScreen{
    map<int, DisplayServerWindow> windows;

    DisplayServerScreen();
    void addWindow(int windowID);
    void remWindow(int windowID);
};

class ServerInterface{
    virtual int getHeight(int screen, int windowID) const = 0;
    virtual int getWidth(int screen, int windowID) const = 0;
    virtual int getPosition(int screen, int windowID) const = 0;
    virtual void setHeight(int screen, int windowID, int height) = 0;
    virtual void setWidth(int screen, int windowID, int width) = 0;
    virtual void setPosition(int screen, int windowID, Point position) = 0;

    virtual void setEventCallback(void update(DisplayServerEvent& ev)) = 0;

};

class DisplayServer : ServerInterface{
    vector<DisplayServerScreen> screens;

    virtual int getHeight(int screen, int windowID) const override;
    virtual int getWidth(int screen, int windowID) const override;
    virtual int getPosition(int screen, int windowID) const override;
    virtual void setHeight(int screen, int windowID, int height) override;
    virtual void setWidth(int screen, int windowID, int width) override;
    virtual void setPosition(int screen, int windowID, Point position) override;

    virtual void setEventCallback(void update(DisplayServerEvent& ev)) override;

    DisplayServer();
};

struct WMWindow{
    unordered_set<Workspace*> tags;
    bool partVertically;

    bool hasTag(Workspace* tag);
    bool addTag(Workspace* tag);
    bool removeTag(Workspace* tag);
};

struct WMWindowNode{
    int windowID;
    int part1Size;
    WMWindow* window;
    WMWindowNode* part1;
    WMWindowNode* part2;

    WMWindowNode();
};


class Workspace {
public:
    Workspace(int workspaceID);
    int getHeight() const;
    int getWidth() const;
    int getPosition() const;
    int getNumWindows() const;

private:
    WMWindowNode* root;
    int height;
    int width;
    int numWindows;
    Point position;

    void setHeight(int height);
    void setWidth(int width);
    void setPosition(Point position);
    bool addWindow(int windowID);
    bool removeWindow(int windowID);
};


class WM {
    WM(ServerInterface* server);
};