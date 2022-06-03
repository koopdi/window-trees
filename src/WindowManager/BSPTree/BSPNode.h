#pragma once

struct BSPNode
{
	bool partVertically;
	double part1Size;
	long windowID;
	BSPNode* part1;
	BSPNode* part2;

	BSPNode(bool partVertically = true, int windowID = -1);

	~BSPNode();

	bool isWindow();
};