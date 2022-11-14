#include "PolygonShape.h"

namespace eq
{
	namespace Physics
	{
		PolygonShape::PolygonShape(Math::Vector2 position, float angle, float sides, Material material, Math::Matrix2x2 scale) :
			Shape(position, angle, ShapeType::Polygon, material, scale), sides(sides)
		{
			Math::Matrix2x2 transform = getScale() * Math::Matrix2x2(getAngle());
			for (float i = 0; i < Math::TWO_PI; i += Math::TWO_PI / sides)
			{
				Math::Vector2 originalPoint(cos(i), sin(i));
				original.push_back(originalPoint);
				transformed.push_back(transform * originalPoint + getPosition());
			}
		}

		void PolygonShape::update(float delta) 
		{
			Shape::update(delta);
			transformPoints();
		}

		void PolygonShape::render()
		{
			for (unsigned int i = 0; i < transformed.size(); i++)
			{
				Renderer::DrawLine(transformed[i], transformed[(i + 1) % transformed.size()], Color(255, 0, 0));
			}
		}

		void PolygonShape::transformPoints()
		{
			for (unsigned int i = 0; i < original.size(); i++)
			{
				Math::Matrix2x2 transform = getScale() * Math::Matrix2x2(getAngle());
				transformed[i] = transform * original[i] + getPosition();
			}
		}

		void PolygonShape::calculateUnits()
		{

		}
	}
}