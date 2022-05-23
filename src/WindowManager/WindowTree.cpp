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
bool WindowTree::contains(int windowID) const {
	bool contains = false;
	/**
	 * @brief find the correct node
	 *
	 * define what we want to do to our nodes as we traverse them
	 * our function must return bool and take in a windowNode pointer
	 * however we can add extra paramaters including return paramaters in the [] brackets */
	std::function<bool(WindowNode*)> func = [&contains, windowID](WindowNode* node) -> bool {
		if (node->windowID == windowID) {  // check
			contains = true;  // check successful
			return false;  // stop looking
		}
		return true;  //  keep looking
	};
	WindowNode* node = root;
	preOrderTraverse(node, func);  // find node in preorder
	return contains;  // return success/failure
}

bool WindowTree::add(bool partVertically, int windowID, double part1Size) {
	add(root, partVertically, windowID, part1Size);
	return true;
}

/**
 * @brief private helper function for adding window nodes
 *
 * @param node
 * @param partVertically
 * @param windowID
 * @param part1Size
 */
void WindowTree::add(WindowNode*& node, bool partVertically, int windowID, double part1Size) {
	//TODO: will WindowIDs be generated in the WindowTree or passed in?
    if(node == nullptr) {
        node = new WindowNode(partVertically, windowID, part1Size);
		size++;
    } /* else if (val > node->data) {
        add(node->right, val);
    } else if (val < node->data) {
        add(node->left, val);
    }
	*/
}

bool WindowTree::remove(int windowID) {
    size--;
    // TODO: remove node
	return 0;
}

void WindowTree::preOrderTraverse(WindowNode* node, const std::function<bool(WindowNode*)>& func) const{
    if (node == nullptr) return;
    // run the function and save result
    bool keepGoing = func(node);
    if (keepGoing) {
      // recurse
    preOrderTraverse(node->part1, func);
    preOrderTraverse(node->part2, func);
	}
}

void WindowTree::inOrderTraverse(WindowNode* node, std::function<bool(WindowNode*)> func) const{
    if (node == nullptr) return;

    inOrderTraverse(node->part1, func);
	bool keepGoing = func(node);
	if (keepGoing) {
    inOrderTraverse(node->part2, func);
	}
}

void WindowTree::postOrderTraverse(WindowNode* node, std::function<bool(WindowNode*)> func) const{
    if (node == nullptr) return;

    postOrderTraverse(node->part1, func);
    postOrderTraverse(node->part2, func);
	func(node);
}
