#include "PhysicsWorld.h"

namespace eq
{
	namespace Physics
	{
		BoxShape* PhysicsWorld::addBox(Math::Vector2 position, float angle, Material material, Math::Vector2 scale, Math::Vector2 velocity, float omega, Math::Vector2 gravity, Color color)
		{
			BoxShape* box = new BoxShape(position, angle, material, Math::Matrix2x2(scale.x, 0, 0, scale.y));
			box->setVelocity(velocity);
			box->setOmega(omega);
			box->setGravity(GRAVITY);
			box->setGravity(gravity);
			box->setColor(color);
			bodies.push_back(box);
			return box;
		}

		CircleShape* PhysicsWorld::addCircle(Math::Vector2 position, float angle, float radius, Material material, Math::Vector2 velocity, float omega, Math::Vector2 gravity, Color color)
		{
			CircleShape* circle = new CircleShape(position, angle, radius, material);
			circle->setVelocity(velocity);
			circle->setOmega(omega);
			circle->setGravity(GRAVITY);
			circle->setGravity(gravity);
			circle->setColor(color);
			bodies.push_back(circle);
			return circle;
		}

		PolygonShape* PhysicsWorld::addPolygon(Math::Vector2 position, float angle, int sides, Material material, Math::Matrix2x2 scale, Math::Vector2 velocity, float omega, Math::Vector2 gravity, Color color)
		{
			PolygonShape* polygon = new PolygonShape(position, angle, sides, material, scale);
			polygon->setVelocity(velocity);
			polygon->setOmega(omega);
			polygon->setGravity(GRAVITY);
			polygon->setGravity(gravity);
			polygon->setColor(color);
			bodies.push_back(polygon);
			return polygon;
		}

		void PhysicsWorld::setWorldGravity(Math::Vector2 gravity)
		{
			this->GRAVITY = gravity;
			for (Shape* body : bodies)
			{
				body->setGravity(GRAVITY);
			}
		}

		void PhysicsWorld::update(float delta)
		{
			for (unsigned int i = 0; i < bodies.size(); i++)
			{
				Shape* body = bodies[i];
				body->update(delta);

				for (unsigned int j = i + 1; j < bodies.size(); j++)
				{
					Shape* colliderBody = bodies[j];
					Manifold manifold = detector.detectCollision(body, colliderBody);
					if (manifold.colliding)
					{
						solver.resolveDynamic(manifold);
					}
				}
			}
		}

		void PhysicsWorld::render()
		{
			for (Shape* body : bodies)
			{
				body->render();
			}
		}
	}
}