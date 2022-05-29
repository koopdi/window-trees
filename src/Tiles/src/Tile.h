// Travis McKinney
// CS132, Winter 2022
// Project 2 (Tiles - Window Manager)
// 1.24.22

// Tile ----------------------------------------------------
//----------------------------------------------------------
// This file contain the Tile class declarations.
// The Tile class implements a rectangualar shape that has a
// color, a width, a height and a position.
// The Tile class implements methods to draw itsself and to
// Check if a given point is contained inside it.
//----------------------------------------------------------

// includes ------------------------------------------------

#include <iostream>
#include <string>
#include "gwindow.h"

using namespace sgl;
using namespace std;

// Tile ----------------------------------------------------

class Tile
{
	// Private data, describing the Tiles position,
	// geometry, and color
 private:
	int x;
	int y;
	int width;
	int height;
	string color;
	GRectangle rect;

	//indicates that this tile needs to be redrawn
	bool dirty;

	// Public Methods
 public:
	// construct a new tile with the specified params: x, y,
	// width, height, color.
	Tile(int x, int y, int width, int height, string color);

	// return the x coordinate of the top left corner
	int getX() const;
	// return the y coordinate of the top left corner
	int getY() const;
	// return the width
	int getWidth() const;
	// return the height
	int getHeight() const;
	// return the color
	string getColor() const;
	// return a rectangle of the idetical shape
	GRectangle getRect() const;

	// check if the Tile contains point (x, y)
	bool contains(int x, int y);
	// check if the tiles are touching
	bool touches(Tile &other);

	// render the tile onto the specified window
	void draw(GWindow &window);
	// display info about the Tile on stdout
	void print();

	// indicate that this tile needs to be redrawn
	void setDirty();
	// indicate that this tile does not need to be redrawn
	void unsetDirty();
	// indicates that this tile needs to be redrawn
	bool isDirty() const;
};