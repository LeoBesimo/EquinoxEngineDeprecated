#pragma once

#include "Shapes/BoxShape.h"
#include "Shapes/CircleShape.h"
#include "Shapes/PolygonShape.h"

namespace eq
{
	namespace Physics
	{
		class PhysicsWorld
		{

		private:
			std::vector<Shape*> bodies;

		private:
			PhysicsWorld();
		
		public:
			static PhysicsWorld& getInstance()
			{
				PhysicsWorld world;
				return world;
			}

			static void AddBody(Shape* body)
			{
				getInstance().bodies.push_back(body);
			}

			static BoxShape* AddBox();
			static CircleShape* AddCircle();
			static PolygonShape* AddPolygon();

			static void Update(float delta);
			static void Render();
		};
	}
}