#include "types.h"

Area Area::operator*(Area other){
	other.x *= x;
	other.y *= y;
	other.width *= width;
	other.height *= height;
	return other;
}

Area Area::operator/(Area& other){
	Area a;
	a.x = x / other.x;
	a.y = y / other.y;
	a.width = width / other.width;
	a.height = height / other.height;
	return a;
}