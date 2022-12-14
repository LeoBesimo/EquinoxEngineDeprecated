#include "CircleShape.h"

namespace eq
{
	namespace Physics
	{
		CircleShape::CircleShape(Math::Vector2 position, float angle, float radius, Material material) :
			Shape(position, angle, ShapeType::Circle, material, Math::Matrix2x2()), radius(radius)
		{
			calculateUnits();
		}

		void CircleShape::update(float delta)
		{
			/*wchar_t buffer[32];
			swprintf(buffer, 32, L"%f : %f\n", getAngle(), getOmega());
			OutputDebugString(buffer);*/
			applyGravity();
			Shape::update(delta);
		}

		void CircleShape::render()
		{
			Math::Vector2 point(radius, 0);
			point = Math::Matrix2x2(getAngle()) * point + getPosition();
			Renderer::DrawLine(getPosition(), point, getColor());
			Renderer::DrawCircle(getPosition(), radius, getColor());
		}

		void CircleShape::applyGravity()
		{
			setForce(getForce() + (getGravit() * getMass()));
		}

		void CircleShape::calculateUnits()
		{
			float area = radius * radius * Math::PI;
			setMass(area * getMaterial().density);
			setInertia(0.5f * getMass() * radius * radius);
		}
	}
}