#include "eqMath.h"

namespace eq
{
	namespace Math
	{
		float pythagoreanSolve(float x, float y)
		{
			return x * x + y * y;
		}

		float fastInvSquareRoot(float n)
		{
			const float threehalfs = 1.5F;
			float y = n;

			long i = *(long*)&y;

			i = 0x5f3759df - (i >> 1);
			y = *(float*)&i;

			y = y * (threehalfs - ((n * 0.5F) * y * y));
			y = y * (threehalfs - ((n * 0.5F) * y * y));

			return y;
		}

		float dot(Vector2 a, Vector2 b)
		{
			return a.x * b.x + a.y * b.y;
		}

		float dot(Vector3 a, Vector3 b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}

		float dot(Vector4 a, Vector4 b)
		{
			return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
		}

		float cross(Vector2 a, Vector2 b)
		{
			return a.x * b.y - a.y * b.x;
		}

		Vector3 cross(Vector3 a, Vector3 b)
		{
			return Vector3(
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
			);
		}

		float square(float n)
		{
			return n * n;
		}
	}
}