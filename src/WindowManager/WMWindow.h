#include <unordered_set>

struct WMWindow{
    std::unordered_set<int> tags;
    bool partVertically;

    bool hasTag(int tag);
    bool addTag(int tag);
    bool removeTag(int tag);
};

struct WMWindowNode{
    int windowID;
    int part1Size;
    WMWindow* window;
    WMWindowNode* part1;
    WMWindowNode* part2;

    WMWindowNode();
};