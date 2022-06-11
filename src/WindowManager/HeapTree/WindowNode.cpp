/**
 * @file WindowNode.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */

#include "WindowNode.h"
#include <iostream>

HeapWindow::HeapWindow(int windowID, Area area)
{
	this->windowID = windowID;
	this->area = area;
	this->left = nullptr;
	this->right = nullptr;

	std::cout << "new Window:" << windowID << " area: " << "(" << area.x << ",";
	std::cout << area.x + area.width << ")x(" << area.y << ",";
	std::cout << area.y + area.height << ")" << std::endl;
}

HeapWindow::HeapWindow
(
	bool partVertically,
	int part1Size,
	HeapWindow* left,
	HeapWindow* right
)
{
	this->partVertically = partVertically;
	this->part1Size = part1Size;
	this->left = left;
	this->right = right;
	this->area = Area{0,0,0,0};
	this->windowID = -1;

	std::cout << "new Window:" << windowID << " area: " << "(" << area.x << ",";
	std::cout << area.x + area.width << ")x(" << area.y << ",";
	std::cout << area.y + area.height << ")" << std::endl;
}

bool HeapWindow::isWindow() const {
  return windowID != -1;
}