#pragma once

#include "Shape.h"

namespace eq
{
	namespace Physics
	{
		class BoxShape : 
			public Shape
		{
		private:
			Math::Vector2 original[4];
			std::vector<Math::Vector2> transformed;

		public:
			BoxShape(Math::Vector2 position, float angle, Material material, Math::Matrix2x2 scale);

			void update(float delta);
			void render();

		public:
			std::vector<Math::Vector2> getCorners() { return transformed; };

		private:
			void applyGravity();
			void transformPoints();
			void calculateUnits();
		};
	}
}