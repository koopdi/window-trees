#include "types.h"

/** @file types.h
 * @brief implements the functions defined in types.h
 * @author Christen Spadavecchia
 * @date 6/10/2022
*/

//implements the * operator for area
Area Area::operator*(Area other){
	other.x *= x;
	other.y *= y;
	other.width *= width;
	other.height *= height;
	return other;
}

//implements the / operator for area
Area Area::operator/(Area other){
	other.x = x / other.x;
	other.y = y / other.y;
	other.width = width / other.width;
	other.height = height / other.height;
	return other;
}

//implements the + operator for area
Area Area::operator+(Area other){
	other.x += x;
	other.y += y;
	other.width += width;
	other.height += height;
	return other;
}

//implements the - operator for area
Area Area::operator-(Area other){
	other.x = x - other.x;
	other.y = y - other.y;
	other.width = width - other.width;
	other.height = height - other.height;
	return other;
}