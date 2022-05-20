#include <unordered_set>

struct Window{
    std::unordered_set<int> tags;
    bool partVertically;

    bool hasTag(int tag);
    bool addTag(int tag);
    bool removeTag(int tag);
};

struct WindowNode{
    int windowID;
    int part1Size;
    Window* window;
    WindowNode* part1;
    WindowNode* part2;

    WindowNode();
};