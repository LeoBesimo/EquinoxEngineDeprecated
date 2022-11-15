#include "CollisionDetector.h"

namespace eq
{
	namespace Physics
	{
		Manifold CollisionDetector::CircleCircleCollision(CircleShape* bodyA, CircleShape* bodyB)
		{
			Manifold manifold;

			Math::Vector2 distance = (bodyB->getPosition() - bodyB->getPosition());
			float distSqr = distance.lenSqr();
			float radiiSqr = bodyA->getRadius() + bodyB->getRadius();
			radiiSqr *= radiiSqr;

			if (distSqr >= radiiSqr)
			{
				manifold.colliding = false;
				return manifold;
			}

			manifold.colliding = true;
			manifold.bodyA = bodyA;
			manifold.bodyB = bodyB;
			manifold.normal = (bodyB->getPosition() - bodyA->getPosition()).normalize();
			manifold.penetration = (bodyA->getRadius() + bodyB->getRadius()) - distance.len();

			return manifold;
		}

		Manifold CollisionDetector::PolygonPolygonCollision(PolygonShape* bodyA, PolygonShape* bodyB)
		{
			return Manifold();
		}

		Manifold CollisionDetector::BoxBoxCollision(BoxShape* bodyA, BoxShape* bodyB)
		{
			return Manifold();
		}

		Manifold CollisionDetector::CircleBoxCollison(CircleShape* bodyA, BoxShape* bodyB)
		{
			return Manifold();
		}

		Manifold CollisionDetector::CirclePolygonCollison(CircleShape* bodyA, PolygonShape* bodyB)
		{
			return Manifold();
		}

		Manifold CollisionDetector::BoxPolygonCollision(BoxShape* bodyA, PolygonShape* bodyB)
		{
			return Manifold();
		}

		CollisionDetector::CollisionDetector()
		{}

		Manifold CollisionDetector::detectCollision(Shape* bodyA, Shape* bodyB)
		{
			switch (bodyA->getShapeType())
			{
			case ShapeType::Box:
			{
				switch (bodyB->getShapeType())
				{
				case ShapeType::Box:
				{
					return BoxBoxCollision(static_cast<BoxShape*>(bodyA), static_cast<BoxShape*>(bodyB));
				}break;

				case ShapeType::Circle:
				{
					return CircleBoxCollison(static_cast<CircleShape*>(bodyB), static_cast<BoxShape*>(bodyA));
				}break;

				case ShapeType::Polygon:
				{
					return BoxPolygonCollision(static_cast<BoxShape*>(bodyA), static_cast<PolygonShape*>(bodyB));
				}break;
				}
			}break;

			case ShapeType::Circle:
			{
				switch (bodyB->getShapeType())
				{
				case ShapeType::Box:
				{
					return CircleBoxCollison(static_cast<CircleShape*>(bodyA), static_cast<BoxShape*>(bodyB));
				}break;

				case ShapeType::Circle:
				{
					return CircleCircleCollision(static_cast<CircleShape*>(bodyA), static_cast<CircleShape*>(bodyB));
				}break;

				case ShapeType::Polygon:
				{
					return CirclePolygonCollison(static_cast<CircleShape*>(bodyA), static_cast<PolygonShape*>(bodyB));
				}break;
				}
			}break;

			case ShapeType::Polygon:
			{
				switch (bodyB->getShapeType())
				{
				case ShapeType::Box:
				{
					return BoxPolygonCollision(static_cast<BoxShape*>(bodyB), static_cast<PolygonShape*>(bodyA));
				}break;

				case ShapeType::Circle:
				{
					return CirclePolygonCollison(static_cast<CircleShape*>(bodyB), static_cast<PolygonShape*>(bodyA));
				}break;

				case ShapeType::Polygon:
				{
					return PolygonPolygonCollision(static_cast<PolygonShape*>(bodyA), static_cast<PolygonShape*>(bodyB));
				}break;
				}
			}break;
			}
		}
	}
}