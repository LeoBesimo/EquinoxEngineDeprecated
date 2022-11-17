#include "CollisionDetector.h"

namespace eq
{
	namespace Physics
	{
		Manifold CollisionDetector::CircleCircleCollision(CircleShape* bodyA, CircleShape* bodyB)
		{
			Manifold manifold;

			Math::Vector2 distanceVector = (bodyB->getPosition() - bodyA->getPosition());
			float distance = distanceVector.lenSqr();
			float radii = bodyA->getRadius() + bodyB->getRadius();

			if (distance >= (radii * radii))
			{
				manifold.colliding = false;
				return manifold;
			}

			manifold.colliding = true;
			manifold.bodyA = bodyA;
			manifold.bodyB = bodyB;
			manifold.penetration = radii - distanceVector.len();
			manifold.normal = distanceVector.normalize();
			manifold.contact = bodyA->getPosition() + (manifold.normal * (bodyA->getRadius() - manifold.penetration));

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