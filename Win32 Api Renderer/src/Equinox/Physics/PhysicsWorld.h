#pragma once

#include "CollisionDetector.h"
#include "CollisionSolver.h"
#include "Shapes/Shapes.h"

namespace eq
{
	namespace Physics
	{
		class PhysicsWorld
		{

		private:
			std::vector<Shape*> bodies;
			CollisionDetector detector;
			CollisionSolver solver;

			Math::Vector2 worldSize;
			float worldBorder;

			Math::Vector2 GRAVITY;

		public:
			PhysicsWorld(Math::Vector2 worldSize) :
				worldSize(worldSize)
			{
				worldBorder = 150;
			}

			void addBody(Shape* body)
			{
				bodies.push_back(body);
			}

			BoxShape* addBox(
				Math::Vector2 position, 
				float angle, 
				Material material, 
				Math::Vector2 scale, 
				Math::Vector2 velocity =  Math::Vector2(),
				float omega = 0,
				Math::Vector2 gravity = Math::Vector2(), 
				Color color = Color(255,255,255)
			);
			CircleShape* addCircle(
				Math::Vector2 position,
				float angle,
				float radius,
				Material material,
				Math::Vector2 velocity = Math::Vector2(),
				float omega = 0,
				Math::Vector2 gravity = Math::Vector2(),
				Color color = Color(255, 255, 255)
			);
			PolygonShape* addPolygon(
				Math::Vector2 position,
				float angle,
				int sides,
				Material material,
				Math::Matrix2x2 scale,
				Math::Vector2 velocity = Math::Vector2(),
				float omega = 0,
				Math::Vector2 gravity = Math::Vector2(),
				Color color = Color(255, 255, 255)
			);

			void setWorldGravity(Math::Vector2 gravity);

			void update(float delta);
			void render();

		private:
			bool inWorld(Shape* shape);
			void removeBody(unsigned int index);
		};
	}
}