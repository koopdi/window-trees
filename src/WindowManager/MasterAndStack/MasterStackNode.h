#pragma once
/** @file
 * MasterStackNode is a linked list node containing a windowID and a next pointer.
 * The struct includes a ctor that takes a windowID
 * and an optional next ptr that defaults to nullptr
 * @author Christen Spadavecchia
 * @date Spring 2022
 * CS 133
*/

/** @brief
 * A struct used to create a linked list of windowIDs
*/
struct MasterStackNode {
	//the id of a window
	long windowID;
	//a pointer to another MasterStackNode
	MasterStackNode* next;

	//constructs a MasterStackNode from a mandatory windowID and an optional next ptr
	MasterStackNode(long windowID, MasterStackNode* next = nullptr);
};