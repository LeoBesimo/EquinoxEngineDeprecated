#pragma once
#include <vector>

#include "Materials.h"
#include "../../Renderer.h"


namespace eq
{
	namespace Physics
	{
		enum class ShapeType
		{
			Box, Polygon, Circle
		};

		class Shape
		{
		private:
			ShapeType type;
			Material material;

			Math::Vector2 position;
			Math::Vector2 velocity;
			Math::Vector2 force;

			float angle;
			float omega;
			float torque;

			Math::Matrix2x2 scale;

			float mass;
			float inertia;
			float invMass;
			float invInertia;


		public:
			Shape(Math::Vector2 position, float angle, ShapeType type, Material material, Math::Matrix2x2 scale);

			void update(float delta);
			virtual void render() = 0;

			void applyForce(Math::Vector2 force, Math::Vector2 radius = Math::Vector2());

		public:
			//Get
			ShapeType getShapeType() { return type; }
			Material getMaterial() { return material; }

			Math::Vector2 getPosition() { return position; }
			Math::Vector2 getVelocity() { return velocity; }
			Math::Vector2 getForce() { return force; }

			float getAngle() { return angle; }
			float getOmega() { return omega; }
			float getTorque() { return torque; }

			Math::Matrix2x2 getScale() { return scale; }

			float getMass() { return mass; }
			float getInertia() { return inertia; }
			float getInvMass() { return invMass; }
			float getInvInertia() { return invInertia; }

			//Set
			void setShapeType(ShapeType type) { this->type = type; }
			void setMaterial(Material material) { this->material = material; }
			
			void setPosition(Math::Vector2 position) { this->position = position; }
			void setVelocity(Math::Vector2 velocity) { this->velocity = velocity; }
			void setForce(Math::Vector2 force) { this->force = force; }

			void setAngle(float angle) { this->angle = angle; }
			void setOmega(float omega) { this->omega = omega; }
			void setTorque(float torque) { this->torque = torque; }

			void setScale(Math::Matrix2x2 scale) { this->scale = scale; }

			void setMass(float mass);
			void setInertia(float inertia);

			void setStatic();

		private:
			void integrateForces(float delta);
			void integrateVelocities(float delta);

			virtual void calculateUnits() = 0;
		};
	}
}