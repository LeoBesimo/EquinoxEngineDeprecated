#include "CollisionDetector.h"

namespace eq
{
	namespace Physics
	{
		float CollisionDetector::distPointToLine(Math::Vector2 point, Math::Vector2 a, Math::Vector2 b, Math::Vector2* closest)
		{
			Math::Vector2 ab = b - a;
			Math::Vector2 ap = point - a;

			float proj = Math::dot(ap, ab);
			float abLenSqr = ab.lenSqr();
			float d = proj / abLenSqr;

			if (d <= 0)
			{
				closest = &a;
			}
			else if (d >= 1.0f)
			{
				closest = &b;
			}
			else
			{
				Math::Vector2 c = (a + (ab * d));
				closest = &c;
			}

			double dx = point.x - closest->x;
			double dy = point.y - closest->y;

			return dx * dx + dy * dy;
		}

		Math::Vector2 CollisionDetector::getContactBoxBox(BoxShape* bodyA, BoxShape* bodyB)
		{
			std::vector<Math::Vector2> pointsA = bodyA->getCorners();
			std::vector<Math::Vector2> pointsB = bodyB->getCorners();
			unsigned int contactCount = 0;

			Math::Vector2 contact1;
			Math::Vector2 contact2;

			double minDistSqr = FLT_MAX;

			Math::Vector2 closest;

			for (unsigned int i = 0; i < 4; i++)
			{

				Math::Vector2 p = pointsA[i];

				for (unsigned int j = 0; j < 4; j++)
				{
					Math::Vector2 a = pointsB[j];
					Math::Vector2 b = pointsB[(j + 1) % 4];

					float distSqr = distPointToLine(p, a, b, &closest);

					if (Math::nearlyEqual(distSqr, minDistSqr))
					{
						if (!nearlyEqual(closest, contact1))
						{
							contactCount = 2;
							contact2 = closest;
						}
					}
					else if (distSqr < minDistSqr)
					{
						minDistSqr = distSqr;
						contactCount = 1;
						contact1 = closest;
					}
				}

			}

			for (unsigned int i = 0; i < 4; i++)
			{

				Math::Vector2 p = pointsB[i];

				for (unsigned int j = 0; j < 4; j++)
				{
					Math::Vector2 a = pointsA[j];
					Math::Vector2 b = pointsA[(j + 1) % 4];

					float distSqr = distPointToLine(p, a, b, &closest);

					if (Math::nearlyEqual(distSqr, minDistSqr))
					{
						if (!nearlyEqual(closest, contact1))
						{
							contactCount = 2;
							contact2 = closest;
						}
					}
					else if (distSqr < minDistSqr)
					{
						minDistSqr = distSqr;
						contactCount = 1;
						contact1 = closest;
					}
				}
			}

			Math::Vector2 contact = contact1;
			if (contactCount == 2) contact = (contact1 + contact2) / 2;

			return contact;
		}

		Math::Vector2 CollisionDetector::getContactPolygonPolygon(PolygonShape* bodyA, PolygonShape* bodyB)
		{
			std::vector<Math::Vector2> pointsA = bodyA->getCorners();
			std::vector<Math::Vector2> pointsB = bodyB->getCorners();
			unsigned int contactCount = 0;

			Math::Vector2 contact1;
			Math::Vector2 contact2;

			double minDistSqr = FLT_MAX;

			Math::Vector2 closest;

			for (unsigned int i = 0; i < pointsA.size(); i++)
			{

				Math::Vector2 p = pointsA[i];

				for (unsigned int j = 0; j < pointsB.size(); j++)
				{
					Math::Vector2 a = pointsB[j];
					Math::Vector2 b = pointsB[(j + 1) % pointsB.size()];

					float distSqr = distPointToLine(p, a, b, &closest);

					if (Math::nearlyEqual(distSqr, minDistSqr))
					{
						if (!nearlyEqual(closest, contact1))
						{
							contactCount = 2;
							contact2 = closest;
						}
					}
					else if (distSqr < minDistSqr)
					{
						minDistSqr = distSqr;
						contactCount = 1;
						contact1 = closest;
					}
				}

			}

			for (unsigned int i = 0; i < pointsB.size(); i++)
			{

				Math::Vector2 p = pointsB[i];

				for (unsigned int j = 0; j < pointsA.size(); j++)
				{
					Math::Vector2 a = pointsA[j];
					Math::Vector2 b = pointsA[(j + 1) % pointsA.size()];

					float distSqr = distPointToLine(p, a, b, &closest);

					if (Math::nearlyEqual(distSqr, minDistSqr))
					{
						if (!nearlyEqual(closest, contact1))
						{
							contactCount = 2;
							contact2 = closest;
						}
					}
					else if (distSqr < minDistSqr)
					{
						minDistSqr = distSqr;
						contactCount = 1;
						contact1 = closest;
					}
				}
			}

			Math::Vector2 contact = contact1;
			if (contactCount == 2) contact = (contact1 + contact2) / 2;

			return contact;
		}

		Math::Vector2 CollisionDetector::getContactBoxPolygon(BoxShape* bodyA, PolygonShape* bodyB)
		{
			std::vector<Math::Vector2> pointsA = bodyA->getCorners();
			std::vector<Math::Vector2> pointsB = bodyB->getCorners();
			unsigned int contactCount = 0;

			Math::Vector2 contact1;
			Math::Vector2 contact2;

			double minDistSqr = FLT_MAX;

			Math::Vector2 closest;

			for (unsigned int i = 0; i < 4; i++)
			{

				Math::Vector2 p = pointsA[i];

				for (unsigned int j = 0; j < pointsB.size(); j++)
				{
					Math::Vector2 a = pointsB[j];
					Math::Vector2 b = pointsB[(j + 1) % pointsB.size()];

					float distSqr = distPointToLine(p, a, b, &closest);

					if (Math::nearlyEqual(distSqr, minDistSqr))
					{
						if (!nearlyEqual(closest, contact1))
						{
							contactCount = 2;
							contact2 = closest;
						}
					}
					else if (distSqr < minDistSqr)
					{
						minDistSqr = distSqr;
						contactCount = 1;
						contact1 = closest;
					}
				}

			}

			for (unsigned int i = 0; i < pointsB.size(); i++)
			{

				Math::Vector2 p = pointsB[i];

				for (unsigned int j = 0; j < 4; j++)
				{
					Math::Vector2 a = pointsA[j];
					Math::Vector2 b = pointsA[(j + 1) % 4];

					float distSqr = distPointToLine(p, a, b, &closest);

					if (Math::nearlyEqual(distSqr, minDistSqr))
					{
						if (!nearlyEqual(closest, contact1))
						{
							contactCount = 2;
							contact2 = closest;
						}
					}
					else if (distSqr < minDistSqr)
					{
						minDistSqr = distSqr;
						contactCount = 1;
						contact1 = closest;
					}
				}
			}

			Math::Vector2 contact = contact1;
			if (contactCount == 2) contact = (contact1 + contact2) / 2;

			return contact;
		}

		std::vector<Math::Vector2> CollisionDetector::getNormals(std::vector<Math::Vector2> corners)
		{
			std::vector<Math::Vector2> normals(corners.size());

			for (unsigned int i = 0; i < corners.size(); i++)
			{
				unsigned int j = (i + 1) % 4;
				Math::Vector2 edge = corners[j] - corners[i];
				normals.push_back(Math::Vector2(-edge.y, edge.x));
			}
			return normals;
		}

		Math::Vector2 CollisionDetector::getMinMax(std::vector<Math::Vector2> corners, Math::Vector2 normal)
		{
			float minProj = Math::dot(corners[0], normal);
			float maxProj = Math::dot(corners[0], normal);

			for (unsigned int i = 1; i < corners.size(); i++)
			{
				double currentProj = Math::dot(corners[i], normal);
				if (currentProj < minProj)
				{
					minProj = currentProj;
				}

				if (currentProj > maxProj)
				{
					maxProj = currentProj;
				}
			}
			return Math::Vector2(minProj, maxProj);
		}

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
			Manifold m;
			
			m.bodyA = bodyA;
			m.bodyB = bodyB;

			std::vector<Math::Vector2> normalsPoly1 = getNormals(bodyA->getCorners());
			std::vector<Math::Vector2> normalsPoly2 = getNormals(bodyB->getCorners());

			bool separated = false;

			Math::Vector2 normal;
			double minDepth = FLT_MAX;

			for (unsigned int i = 0; i < normalsPoly1.size(); i++)
			{
				Math::Vector2 projectionPoly1 = getMinMax(bodyA->getCorners(), normalsPoly1[i]);
				Math::Vector2 projectionPoly2 = getMinMax(bodyB->getCorners(), normalsPoly1[i]);

				separated = projectionPoly1.x >= projectionPoly2.y || projectionPoly2.x >= projectionPoly1.y;
				if (separated) break;

				float depth = min(projectionPoly2.y - projectionPoly1.x, projectionPoly1.y - projectionPoly2.x);

				if (depth < minDepth)
				{
					minDepth = depth;
					normal = normalsPoly1[i];
				}
			}

			if (!separated)
			{
				for (unsigned int i = 0; i < normalsPoly2.size(); i++)
				{
					Math::Vector2 projectionPoly1 = getMinMax(bodyA->getCorners(), normalsPoly2[i]);
					Math::Vector2 projectionPoly2 = getMinMax(bodyB->getCorners(), normalsPoly2[i]);


					separated = projectionPoly1.x >= projectionPoly2.y || projectionPoly2.x >= projectionPoly1.y;
					if (separated) break;

					float depth = min(projectionPoly2.y - projectionPoly1.x, projectionPoly1.y - projectionPoly2.x);

					if (depth < minDepth)
					{
						minDepth = depth;
						normal = normalsPoly2[i];
					}
				}
			}

			m.colliding = !separated;

			if (!separated)
			{
				Math::Vector2 ab = bodyA->getPosition() - bodyB->getPosition();

				if (Math::dot(ab, normal) < 0) normal *= -1;

				m.penetration = minDepth / normal.len();
				m.normal = normal.normalize();
				m.contact = getContactPolygonPolygon(bodyA, bodyB);
			}

			return m;
		}

		Manifold CollisionDetector::BoxBoxCollision(BoxShape* bodyA, BoxShape* bodyB)
		{
			Manifold m;

			m.bodyA = bodyA;
			m.bodyB = bodyB;

			std::vector<Math::Vector2> normalsPoly1 = getNormals(bodyA->getCorners());
			std::vector<Math::Vector2> normalsPoly2 = getNormals(bodyB->getCorners());

			bool separated = false;

			Math::Vector2 normal;
			double minDepth = FLT_MAX;

			for (unsigned int i = 0; i < normalsPoly1.size(); i++)
			{
				Math::Vector2 projectionPoly1 = getMinMax(bodyA->getCorners(), normalsPoly1[i]);
				Math::Vector2 projectionPoly2 = getMinMax(bodyB->getCorners(), normalsPoly1[i]);

				separated = projectionPoly1.x >= projectionPoly2.y || projectionPoly2.x >= projectionPoly1.y;
				if (separated) break;

				float depth = min(projectionPoly2.y - projectionPoly1.x, projectionPoly1.y - projectionPoly2.x);

				if (depth < minDepth)
				{
					minDepth = depth;
					normal = normalsPoly1[i];
				}
			}

			if (!separated)
			{
				for (unsigned int i = 0; i < normalsPoly2.size(); i++)
				{
					Math::Vector2 projectionPoly1 = getMinMax(bodyA->getCorners(), normalsPoly2[i]);
					Math::Vector2 projectionPoly2 = getMinMax(bodyB->getCorners(), normalsPoly2[i]);


					separated = projectionPoly1.x >= projectionPoly2.y || projectionPoly2.x >= projectionPoly1.y;
					if (separated) break;

					float depth = min(projectionPoly2.y - projectionPoly1.x, projectionPoly1.y - projectionPoly2.x);

					if (depth < minDepth)
					{
						minDepth = depth;
						normal = normalsPoly2[i];
					}
				}
			}

			m.colliding = !separated;

			if (!separated)
			{
				Math::Vector2 ab = bodyA->getPosition() - bodyB->getPosition();

				if (Math::dot(ab, normal) < 0) normal *= -1;

				m.penetration = minDepth / normal.len();
				m.normal = normal.normalize();
				m.contact = getContactBoxBox(bodyA, bodyB);
			}

			return m;
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
			Manifold m;

			m.bodyA = bodyA;
			m.bodyB = bodyB;

			std::vector<Math::Vector2> normalsPoly1 = getNormals(bodyA->getCorners());
			std::vector<Math::Vector2> normalsPoly2 = getNormals(bodyB->getCorners());

			bool separated = false;

			Math::Vector2 normal;
			double minDepth = FLT_MAX;

			for (unsigned int i = 0; i < normalsPoly1.size(); i++)
			{
				Math::Vector2 projectionPoly1 = getMinMax(bodyA->getCorners(), normalsPoly1[i]);
				Math::Vector2 projectionPoly2 = getMinMax(bodyB->getCorners(), normalsPoly1[i]);

				separated = projectionPoly1.x >= projectionPoly2.y || projectionPoly2.x >= projectionPoly1.y;
				if (separated) break;

				float depth = min(projectionPoly2.y - projectionPoly1.x, projectionPoly1.y - projectionPoly2.x);

				if (depth < minDepth)
				{
					minDepth = depth;
					normal = normalsPoly1[i];
				}
			}

			if (!separated)
			{
				for (unsigned int i = 0; i < normalsPoly2.size(); i++)
				{
					Math::Vector2 projectionPoly1 = getMinMax(bodyA->getCorners(), normalsPoly2[i]);
					Math::Vector2 projectionPoly2 = getMinMax(bodyB->getCorners(), normalsPoly2[i]);


					separated = projectionPoly1.x >= projectionPoly2.y || projectionPoly2.x >= projectionPoly1.y;
					if (separated) break;

					float depth = min(projectionPoly2.y - projectionPoly1.x, projectionPoly1.y - projectionPoly2.x);

					if (depth < minDepth)
					{
						minDepth = depth;
						normal = normalsPoly2[i];
					}
				}
			}

			m.colliding = !separated;

			if (!separated)
			{
				Math::Vector2 ab = bodyA->getPosition() - bodyB->getPosition();

				if (Math::dot(ab, normal) < 0) normal *= -1;

				m.penetration = minDepth / normal.len();
				m.normal = normal.normalize();
				m.contact = getContactBoxPolygon(bodyA, bodyB);
			}

			return m;
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