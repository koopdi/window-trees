#include "windowtree.h"

WindowTree::WindowTree() {};
int WindowTree::getSize() const {
    return size;
}

int WindowTree::getNumWindows() const {
	return numWindows;
}

WindowNode* WindowTree::get(int windowID) {
	return 0;
}
bool WindowTree::isEmpty() const{
	return 0;
}
bool WindowTree::contains() const {
	return 0;
}
bool WindowTree::add() {
    size++;
    // TODO: add node
	return 0;
}

bool WindowTree::remove(int windowID) {
    size--;
    // TODO: remove node
	return 0;
}

void WindowTree::preOrderTraverse(WindowNode* node, std::function<WindowNode*(WindowNode*)> func) {

}

void preOrderTraverse(WindowNode* node, std::function<WindowNode*(WindowNode*)> func) {
    if (node == nullptr) return;

    WindowNode* found = func(node);
    if (found == nullptr) {
        preOrderTraverse(node->part1, func);
        preOrderTraverse(node->part2, func);
    }
}

