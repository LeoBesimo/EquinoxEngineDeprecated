#pragma once

#include "Shape.h"

namespace eq
{
	namespace Physics
	{
		class PolygonShape :
			public Shape
		{
		private:
			std::vector<Math::Vector2> original;
			std::vector<Math::Vector2> transformed;
			float sides;

		public:
			PolygonShape(Math::Vector2 position, float angle, float sides, Material material, Math::Matrix2x2 scale);

			void update(float delta);
			void render();

			std::vector<Math::Vector2> getCorners() { return this->transformed; }

		private:
			void applyGravity();
			void transformPoints();
			void calculateUnits();
		};
	}
}