#ifndef _WINDOW_NODE_
#define _WINDOW_NODE_

#include <unordered_set>


struct WindowPane{
    std::unordered_set<int> tags;

    bool hasTag(int tag);
    bool addTag(int tag);
    bool removeTag(int tag);
};

struct WindowNode{
	WindowNode(bool partVertically, int windowID, double part1Size);

	bool partVertically;
    int windowID;
    double part1Size;
    WindowPane* window;
    WindowNode* part1;
    WindowNode* part2;

    WindowNode();
};

#endif