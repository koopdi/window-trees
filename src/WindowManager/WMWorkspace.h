class WMWorkspace {
public:
    WMWorkspace(int workspaceID);
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