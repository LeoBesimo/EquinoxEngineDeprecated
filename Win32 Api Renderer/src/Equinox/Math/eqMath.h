#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix2x2.h"

namespace eq
{
	namespace Math
	{
		const float PI = (float)atan(1) * 4;
		const float QUARTER_PI = (float)(PI / 4.0);
		const float HALF_PI = (float)(PI / 2.0);
		const float TWO_PI = (float)(PI * 2.0);
		const float E = (float)(2.7182818284590452353602874713527);

		float pythagoreanSolve(float x, float y);
		float fastInvSquareRoot(float n);

		float dot(Vector2 a, Vector2 b);
		float dot(Vector3 a, Vector3 b);
		float dot(Vector4 a, Vector4 b);

		float cross(Vector2 a, Vector2 b);
		Vector3 cross(Vector3 a, Vector3 b);

		float square(float n);
	}
}