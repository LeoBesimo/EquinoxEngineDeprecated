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

		const float THRESHOLD = 1.0f;

		float pythagoreanSolve(float x, float y);
		float pythagoreanSolve(float x, float y, float z);
		float pythagoreanSolve(float w, float x, float y, float z);
		float pythagoreanSolve(Vector2 a, Vector2 b);
		float pythagoreanSolve(Vector3 a, Vector3 b);
		float pythagoreanSolve(Vector4 a, Vector4 b);
		float fastInvSquareRoot(float n);

		float dot(Vector2 a, Vector2 b);
		float dot(Vector3 a, Vector3 b);
		float dot(Vector4 a, Vector4 b);

		float cross(Vector2 a, Vector2 b);
		Vector3 cross(Vector3 a, Vector3 b);

		float square(float n);

		bool nearlyEqual(float a, float b);
		bool nearlyEqual(Vector2 a, Vector2 b);
		bool nearlyEqual(Vector3 a, Vector3 b);
		bool nearlyEqual(Vector4 a, Vector4 b);

		float distPointToLine(Vector2 point, Vector2 a, Vector2 b, Vector2* closest);

	}
}