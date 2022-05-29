// Travis McKinney
// CS132, Winter 2022
// Project 2 (Tiles - Window Manager)
// 1.24.22

// Tile Manager --------------------------------------------
//----------------------------------------------------------
// This file contains the TileManager class declarations.
// The TileManager class implements a data structure to store
// Tile objects, and methods to manage those objects.
//----------------------------------------------------------

// includes ------------------------------------------------

#include "Tile.h"
#include "gwindow.h"

using namespace sgl;

class TileManager
{
	// Private data, a vector to store Tiles
 private:
	vector<Tile> tileDex;

	// Private Methods
 private:
	// Set the dirty flag on the tile at idxTile in the tileDex.
	// Set the dirty flag on all tiles above idxTile, which overlap idxTile.
	// Recurse to find those tiles, which overlap the overlappers.
	void stackDirty(size_t idxTile);

	// Public Methods
 public:
	// Return the index of the topmost Tile, which contains point (x,y) or
	// return -1, if no tile contains that point.
	int getTopAt(int x, int y);
	// Insert a new Tile into the tileDex, at the lowest z-order.
	void addBottom(Tile &rect);
	// Insert a new Tile into the tileDex, at the highest z-order.
	void addTop(Tile &rect);
	// Draw all the Tiles in the tileDex
	void drawAll(GWindow &window);
	// Draw all the Tiles marked dirty
	void drawDirty(GWindow &window);
	// Erase all the tiles in the tileDex
	void clear();
	// Render a yellow border around the top-most Tile,
	// which contains point (x,y), onto window.
	void highlight(int x, int y, GWindow &window);
	// Move the top-most Tile,
	// which contains point (x,y), to the highest z-order.
	void raise(int x, int y);
	// Move the top-most Tile,
	// which contains point (x,y), to the lowest z-order.
	void lower(int x, int y);
	// Remove the top-most Tile,
	// which contains point (x,y), from the tileDex.
	void remove(int x, int y);
	// Remove every Tile,
	// which contains point (x,y), from the tileDex.
	void removeAll(int x, int y);
};