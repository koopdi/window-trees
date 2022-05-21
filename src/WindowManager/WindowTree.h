#include <functional>

#include "WindowNode.h"

class WindowTree {
public:
    WindowTree();
    bool add();
    bool remove(int windowID);
    WindowNode* get(int windowID);

    bool isEmpty() const;
    bool contains() const;
    int getSize() const;
    int getNumWindows() const;

private:
    void preOrderTraverse(WindowNode* node, std::function<WindowNode*(WindowNode*)> func);
    void inOrderTraverse(WindowNode* node, std::function<WindowNode*(WindowNode*)> func);
    void postOrderTraverse(WindowNode* node, std::function<WindowNode*(WindowNode*)> func);

	int numWindows;
    int size;
    WindowNode* root;
};