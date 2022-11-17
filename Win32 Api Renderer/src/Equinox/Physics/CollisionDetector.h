#pragma once

#include "../Math/eqMath.h"
#include "Shapes/Shapes.h"

namespace eq
{
	namespace Physics
	{
		struct Manifold
		{
			bool colliding;
			Shape* bodyA;
			Shape* bodyB;
			Math::Vector2 normal;
			float penetration;
			Math::Vector2 contact;
		};

		class CollisionDetector
		{
		private:
			Math::Vector2 getContactBoxBox(BoxShape* bodyA, BoxShape* bodyB);
			Math::Vector2 getContactPolygonPolygon(PolygonShape* bodyA, PolygonShape* bodyB);
			Math::Vector2 getContactBoxPolygon(BoxShape* bodyA, PolygonShape* bodyB);
			Math::Vector2 getContactCircleBox(CircleShape* bodyA, BoxShape* bodyB);
			Math::Vector2 getcontactCirclePolygon(CircleShape* bodyA, PolygonShape* bodyB);

			std::vector<Math::Vector2> getNormals(std::vector<Math::Vector2> corners);

			Math::Vector2 getMinMax(std::vector<Math::Vector2> points, Math::Vector2 normal);

			Manifold CircleCircleCollision(CircleShape* bodyA, CircleShape* bodyB);
			Manifold PolygonPolygonCollision(PolygonShape* bodyA, PolygonShape* bodyB);
			Manifold BoxBoxCollision(BoxShape* bodyA, BoxShape* bodyB);

			Manifold CircleBoxCollison(CircleShape* bodyA, BoxShape* bodyB);
			Manifold CirclePolygonCollison(CircleShape* bodyA, PolygonShape* bodyB);
			Manifold BoxPolygonCollision(BoxShape* bodyA, PolygonShape* bodyB);

		public:
			CollisionDetector();

			Manifold detectCollision(Shape* bodyA, Shape* bodyB);

		};
	}
}