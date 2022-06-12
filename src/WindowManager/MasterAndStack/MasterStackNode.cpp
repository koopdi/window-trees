#include "MasterStackNode.h"
/** @file
 * MasterStackNode.cpp provides implementations for MasterStackNode's methods
 *
 * Namely, it provides an implementation of the ctor described in MasterStackNode.h
 * @author Christen Spadavecchia
 * @date Spring 2022
 * CS 133
*/


/// @brief MasterStackNode(windowID, nextPtr) ctor
MasterStackNode::MasterStackNode(long windowID, MasterStackNode* next) :
	windowID(windowID), next(next){}