#include <math.h>
#include <Ymath.h>

namespace Math
{
	const double PI = 3.141592653589793;

	struct Point2D
	{
		float x;
		float y;
	};

	Point2D Rotate2D(float x, float y, float angle)
	{
		Point2D point;
		point.x = x * cos(toRadians(angle)) - y * sin(toRadians(angle));
		point.y = x * sin(angle) + y * cos(angle);
		return point;
	}

	float RotateX(float x, float y, float angle)
	{
		return x * cos(toRadians(angle)) - y * sin(toRadians(angle));
	}

	float RotateY(float x, float y, float angle)
	{
		return x * sin(toRadians(angle)) + y * cos(toRadians(angle));
	}

	float toRadians(float degrees)
	{
		return degrees * PI / 180;
	}
};