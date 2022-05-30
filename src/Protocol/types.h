#ifndef TYPES_H
#define TYPES_H
struct Point
{
	int x;
	int y;
};

struct Area
{
	/**
	 * @brief All values will default to -1.
	 * @param x X position (of which corner?)
	 * @param y Y position (of which corner?)
	 * @param width Width of the rectangle.
	 * @param height Height of the rectangle.
	 */
	Area(int x = -1, int y = -1, int width = -1, int height = -1);
	int x;
	int y;
	int width;
	int height;
};
#endif
