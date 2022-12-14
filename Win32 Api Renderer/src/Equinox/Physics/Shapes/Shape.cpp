#include "Shape.h"

namespace eq
{
	namespace Physics
	{
		Shape::Shape(Math::Vector2 position, float angle, ShapeType type, Material material, Math::Matrix2x2 scale) :
			position(position), angle(angle), type(type), material(material), scale(scale), color(255, 255, 255)
		{
			velocity = Math::Vector2();
			force = Math::Vector2();
			omega = 0;
			torque = 0;
		}

		void Shape::update(float delta)
		{
			integrateForces(delta);
			integrateVelocities(delta);
		}

		void Shape::applyForce(Math::Vector2 force)
		{
			this->force += force;
		}

		void Shape::applyForce(Math::Vector2 force, Math::Vector2 radius)
		{
				torque += Math::cross(force, radius);
		}

		void Shape::setMass(float mass)
		{
			this->mass = mass;
			this->invMass = mass == 0 ? 0 : 1 / mass;
		}

		void Shape::setInertia(float inertia)
		{
			this->inertia = inertia;
			this->invInertia = inertia == 0 ? 0 : 1 / inertia;
		}

		void Shape::setStatic()
		{
			setMass(0);
			setInertia(0);
		}

		void Shape::move(Math::Vector2 distance)
		{
			if (invMass == 0) return;
			this->position += distance;
		}

		void Shape::integrateForces(float delta)
		{
			velocity += force * invMass * delta;
			omega += (torque * invInertia * delta);
			force *= 0;
			torque = 0;
		}

		void Shape::integrateVelocities(float delta)
		{
			position += velocity * delta;
			angle += omega * delta;
		}
	}
}