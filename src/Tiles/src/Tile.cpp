// Travis McKinney
// CS132, Winter 2022
// Project 2 (Tiles - Window Manager)
// 1.24.22

// Tile CPP ------------------------------------------------
//----------------------------------------------------------
// This file contains the Tile class definitions.
// See Tile.h for a high level overview.
//----------------------------------------------------------

// includes ------------------------------------------------

#include "Tile.h"

// Tile CPP ------------------------------------------------

// No defaults are provided,
// so all constructor arguments are mandatory.
Tile::Tile(int x, int y, int width, int height, string color)
	: x(x), y(y), width(width), height(height), color(color), rect(x, y, width, height)
{
}

int Tile::getX() const { return x; }
int Tile::getY() const { return y; }
int Tile::getWidth() const { return width; }
int Tile::getHeight() const { return height; }
string Tile::getColor() const { return color; }

// This function assumes that the origin is at the top-left,
// remember to invert the y coordinate,
// to map from a bottom-left origin!
bool Tile::contains(int xPos, int yPos)
{
	if (x <= xPos && xPos <= x + width && y <= yPos && yPos <= y + height)
	{
		return true;
	}
	return false;
}

GRectangle Tile::getRect() const
{
	return rect;
}

bool Tile::touches(Tile &other)
{
	return rect.intersects(other.getRect());
}

// this function calls SGL draw methods,
// and renders this Tile onto the provided window
void Tile::draw(GWindow &window)
{
	// reset all SGL parameters to the desired values,
	// as they may have been modified during other function calls.
	window.setLineWidth(1);
	window.setColor("black");
	window.setFillColor(color);

	window.fillRect(x, y, width, height);

	unsetDirty();
}

void Tile::print()
{
	cout << "x = " << x << ", "
		 << "y = " << y << ", "
		 << "width = " << width << ", "
		 << "height = " << height << ", "
		 << "color = " << color << endl;
}

void Tile::setDirty()
{
	dirty = true;
}

void Tile::unsetDirty()
{
	dirty = false;
}

bool Tile::isDirty() const
{
	return dirty;
}
