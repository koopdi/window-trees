#pragma once

struct BSPNode
{
	static const short precision = 10000;
	bool partVertically;
	short part1PerPrecision;
	long windowID;
	BSPNode* part1;
	BSPNode* part2;

	BSPNode(bool partVertically = true, int windowID = -1, short part1PerPrecision = 100);

	~BSPNode();

	bool isWindow();
};