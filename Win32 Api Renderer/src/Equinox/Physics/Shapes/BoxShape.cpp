#include "BoxShape.h"

namespace eq
{
	namespace Physics
	{
		BoxShape::BoxShape(Math::Vector2 position, float angle, Material material, Math::Matrix2x2 scale) :
			Shape(position, angle, ShapeType::Box, material, scale)
		{
			original[0] = Math::Vector2(-1, -1);
			original[1] = Math::Vector2(1, -1);
			original[2] = Math::Vector2(1, 1);
			original[3] = Math::Vector2(-1, 1);
			transformed.reserve(4);
			
			for (unsigned int i = 0; i < 4; i++)
				transformed.push_back(Math::Vector2());
			
			transformPoints();
			calculateUnits();
		}

		void BoxShape::update(float delta)
		{
			applyGravity();
			Shape::update(delta);
			transformPoints();
		}

		void BoxShape::render()
		{
			Renderer::DrawLine(transformed[0], transformed[1], getColor());
			Renderer::DrawLine(transformed[1], transformed[2], getColor());
			Renderer::DrawLine(transformed[2], transformed[3], getColor());
			Renderer::DrawLine(transformed[0], transformed[3], getColor());
		}

		void BoxShape::transformPoints()
		{
			Math::Matrix2x2 rotation(getAngle());
			Math::Matrix2x2 transform = rotation * getScale();

			transformed[0] = transform * original[0] + getPosition();
			transformed[1] = transform * original[1] + getPosition();
			transformed[2] = transform * original[2] + getPosition();
			transformed[3] = transform * original[3] + getPosition();

			wchar_t charBuffer[128];
			swprintf(charBuffer, 128, L"%f, %f \n%f, %f \n\n", transform.a.x, transform.b.x, transform.a.y, transform.b.y);
			OutputDebugString(charBuffer);
			//eq::Renderer::WriteText(charBuffer, 50, 50, eq::Color(255, 0, 255));
		}

		void BoxShape::applyGravity()
		{
			applyForce(getGravit() * getMass());

			for (byte i = 0; i < 4; i++)
			{
				Math::Vector2 radius = transformed[i] - getPosition();
				applyForce(getGravit() * getInertia() * 0.25, radius);
			}
		}

		void BoxShape::calculateUnits()
		{
			Math::Matrix2x2 scale = getScale();
			float width = scale.a.x + scale.a.x;
			float height = scale.b.y + scale.b.y;
			float area = width * height;
			setMass(area * getMaterial().density);
			setInertia((1.f / 12.f) * getMass() * (width * width + height * height));
		}
	}
}