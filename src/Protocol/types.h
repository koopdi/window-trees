/** @file types.h
 * @brief defines common types used throughout the project
 * @author Christen Spadavecchia, Travis McKinney
 * @date 6/10/2022
*/

#ifndef TYPES_H
#define TYPES_H

// Use a return type to define an in-header class constant.
// E.G. OMEGA_CONST name = string("Travis");
#define OMEGA_CONST inline static constexpr auto

/** @brief defines a point struct containing an x and y */
struct Point
{
	//the x value of the point
	int x;
	//the y value of the point
	int y;
};

/** @brief defines an area struct with x, y, w, h and *, /, +, -
 * @note often used for the bounding box of windows
*/
struct Area
{
	//upper left x pos
	int x;
	//upper right y pos
	int y;
	//width
	int width;
	//height
	int height;

	/** @brief multiplies each field of an Area
	 * @param other the other area involved in the operation
	 */
	Area operator*(Area other);
	/** @brief divides each field of an Area
	 * @param other the other area involved in the operation
	 */
	Area operator/(Area other);
	/** @brief adds each field of an Area
	 * @param other the other area involved in the operation
	 */
	Area operator+(Area other);
	/** @brief subtracts each field of an Area
	 * @param other the other area involved in the operation
	 */
	Area operator-(Area other);
};

#endif
