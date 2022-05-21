#ifndef _WINDOW_NODE_
#define _WINDOW_NODE_

#include <unordered_set>


struct WindowPane{
    std::unordered_set<int> tags;
    bool partVertically;

    bool hasTag(int tag);
    bool addTag(int tag);
    bool removeTag(int tag);
};

struct WindowNode{
    int windowID;
    int part1Size;
    WindowPane* window;
    WindowNode* part1;
    WindowNode* part2;

    WindowNode();
};

#endif