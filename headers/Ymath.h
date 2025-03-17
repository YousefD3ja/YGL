#ifndef Y_MATH_H
#define Y_MATH_H

#include <math.h>

namespace Math
{
	//static const double PI = 3.141592653589793;
	// 2D point structure
	struct Point2D;

	// Rotate a 2D point by a degree angle
	Point2D Rotate2D(float x, float y, float angle);

	// Rotate an x value by a degree angle
	float RotateX(float x, float y, float angle);

	// Rotate a y value by an angle
	float RotateY(float x, float y, float angle);

	// Convert degrees to radians
	float toRadians(float degrees);
}
#endif