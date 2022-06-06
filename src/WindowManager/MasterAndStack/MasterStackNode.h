#pragma once

struct MasterStackNode {
	long windowID;
	MasterStackNode* next;

	MasterStackNode(long windowID, MasterStackNode* next = nullptr);
};