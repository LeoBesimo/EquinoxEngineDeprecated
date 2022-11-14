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
			Math::Vector2 transformed[4];

		public:
			BoxShape(Math::Vector2 position, float angle, Material material, Math::Matrix2x2 scale);

			void update(float delta);
			void render();

		private:
			void transformPoints();
			void calculateUnits();
		};
	}
}