#pragma once

#include <functional>

#include "WindowNode.h"

class WindowTree {
public:
    WindowTree();
    bool add(bool partVertically, int windowID, double part1Size);
    bool remove(int windowID);
    WindowNode* get(int windowID);

    bool isEmpty() const;
    bool contains(int windowID) const;
    int getSize() const;
    int getNumWindows() const;

private:
    void preOrderTraverse(WindowNode* node, const std::function<bool(WindowNode*)>& func) const;
    void inOrderTraverse(WindowNode* node, std::function<bool(WindowNode*)> func) const;
    void postOrderTraverse(WindowNode* node, std::function<bool(WindowNode*)> func) const;
	void add(WindowNode*& node, bool partVertically, int windowID, double part1Size);

	int numWindows;
    int size;
    WindowNode* root;
};