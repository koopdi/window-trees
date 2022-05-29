// Travis McKinney
// CS132, Winter 2022
// Project 2 (Tiles - Window Manager)
// 1.24.22

// Tile Manager CPP ----------------------------------------
//----------------------------------------------------------
// This file contains the TileManager class definitions.
// See TileManager.h for a high level overview.
//----------------------------------------------------------

// includes ------------------------------------------------

#include "TileManager.h"

// The beginning of tileDex contains the lowest z-order Tile
int TileManager::getTopAt(int x, int y)
{
	// This loop traverses the tileDex lineary, from back to front.
	for (int idxTile = tileDex.size() - 1; idxTile >= 0; idxTile--)
	{
		if (tileDex[idxTile].contains(x, y))
		{
			return idxTile;
		}
	}

	return EOF;
}

// Insert a tile at the beginning of the tileDex
void TileManager::addBottom(Tile &rect) { tileDex.insert(tileDex.cbegin(), rect); }

// Insert a tile at the end of the tileDex
void TileManager::addTop(Tile &rect) { tileDex.insert(tileDex.cend(), rect); }

// Traverse the tileDex from beginning to end and call each Tile's draw method.
void TileManager::drawAll(GWindow &window)
{
	for (Tile &t : tileDex)
	{
		t.draw(window);
	}
}

void TileManager::drawDirty(GWindow &window)
{
	for (size_t idxTile = 0; idxTile < tileDex.size(); idxTile++)
	{
		Tile &t = tileDex[idxTile];
		if (t.isDirty())
		{
			t.draw(window);
			t.unsetDirty();
		}
	}
	// for (Tile &t : tileDex)
	// {
	// 	if (t.isDirty())
	// 	{
	// 		t.draw(window);
	// 		t.unsetDirty();
	// 	}
	// }
}

void TileManager::stackDirty(size_t idxTile)
{
	Tile &t = tileDex[idxTile];
	t.setDirty();

	for(size_t next = idxTile+1; next < tileDex.size(); next++)
	{
		if (t.touches(tileDex[next]))
		{
			stackDirty(next);
		}
	}
}

void TileManager::clear() { tileDex.clear(); }

// This function assumes that the origin is at the top-left,
// remember to invert the y coordinate,
// to map from a bottom-left origin!
void TileManager::highlight(int x, int y, GWindow &window)
{
	int idxTile = getTopAt(x, y);

	if (idxTile != EOF)
	{
		Tile &t = tileDex[idxTile];

		window.setColor("yellow");
		window.setLineWidth(10);
		window.drawRect(t.getX() - 5, t.getY() - 5, t.getWidth() + 10, t.getHeight() + 10);
	}
}

// Move the selected Tile to the end of the tileDex.
void TileManager::raise(int x, int y)
{
	int idxTile = getTopAt(x, y);

	if (idxTile != EOF)
	{
		Tile &t = tileDex[idxTile];
		tileDex.push_back(t);
		tileDex.erase(tileDex.begin() + idxTile);
		tileDex.back().setDirty();
	}
}

// Move the selected Tile to the beginning of the tileDex.
void TileManager::lower(int x, int y)
{
	int idxTile = getTopAt(x, y);

	if (idxTile != EOF)
	{
		Tile &t = tileDex[idxTile];
		tileDex.insert(tileDex.begin(), t);
		// erase old tile, accounting for insertion shift
		tileDex.erase(tileDex.begin() + idxTile + 1);
		stackDirty(0);
	}
}

void TileManager::remove(int x, int y)
{
	int idxTile = getTopAt(x, y);

	if (idxTile != EOF)
	{
		tileDex.erase(tileDex.begin() + idxTile);
	}
}

void TileManager::removeAll(int x, int y)
{
	int idxTile = getTopAt(x, y);

	while (idxTile != EOF)
	{
		tileDex.erase(tileDex.begin() + idxTile);
		idxTile = getTopAt(x, y);
	}
}