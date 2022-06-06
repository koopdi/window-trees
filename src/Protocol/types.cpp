#include "types.h"

Area Area::operator*(Area other){
	other.x *= x;
	other.y *= y;
	other.width *= width;
	other.height *= height;
	return other;
}

Area Area::operator/(Area other){
	other.x = x / other.x;
	other.y = y / other.y;
	other.width = width / other.width;
	other.height = height / other.height;
	return other;
}

Area Area::operator+(Area other){
	other.x += x;
	other.y += y;
	other.width += width;
	other.height += height;
}

Area Area::operator-(Area other){
	other.x = x - other.x;
	other.y = y - other.y;
	other.width = width - other.width;
	other.height = height - other.height;
}