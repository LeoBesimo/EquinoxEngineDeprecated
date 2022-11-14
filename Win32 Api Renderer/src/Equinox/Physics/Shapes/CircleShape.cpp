#include "CircleShape.h"

namespace eq
{
	namespace Physics
	{
		CircleShape::CircleShape(Math::Vector2 position, float angle, float radius, Material material) :
			Shape(position, angle, ShapeType::Circle, material, Math::Matrix2x2()), radius(radius)
		{}

		void CircleShape::update(float delta)
		{
			Shape::update(delta);
		}

		void CircleShape::render()
		{
			Math::Vector2 point(radius, 0);
			point = Math::Matrix2x2(getAngle()) * point + getPosition();
			Renderer::DrawLine(getPosition(), point, Color(0,255,0));
			Renderer::DrawCircle(getPosition(), radius, Color(0, 255, 0));
		}

		void CircleShape::calculateUnits()
		{
			float area = radius * radius * Math::PI;
			setMass(area * getMaterial().density);
			setInertia(0.5f * getMass() * radius * radius);
		}
	}
}