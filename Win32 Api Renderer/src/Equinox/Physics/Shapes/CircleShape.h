#pragma once

#include "Shape.h"

namespace eq
{
	namespace Physics
	{
		class CircleShape :
			public Shape
		{
		private:
			float radius;

		public:
			CircleShape(Math::Vector2 position, float angle, float radius, Material material);

			void update(float delta);
			void render();
		
		private:
			void applyGravity();
			void calculateUnits();
		};
	}
}