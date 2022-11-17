#include "PolygonShape.h"

namespace eq
{
	namespace Physics
	{
		PolygonShape::PolygonShape(Math::Vector2 position, float angle, float sides, Material material, Math::Matrix2x2 scale) :
			Shape(position, angle, ShapeType::Polygon, material, scale), sides(sides)
		{
			Math::Matrix2x2 transform = getScale() * Math::Matrix2x2(getAngle());
			float ac = Math::TWO_PI / sides;
			float maxAngle = sides <= 6 ? Math::TWO_PI : Math::TWO_PI - ac;
			for (float i = 0; i < maxAngle; i += ac)
			{
				Math::Vector2 originalPoint(cos(i), sin(i));
				original.push_back(originalPoint);
				transformed.push_back(transform * originalPoint + getPosition());
			}
			calculateUnits();
		}

		void PolygonShape::update(float delta) 
		{
			applyGravity();
			Shape::update(delta);
			transformPoints();
		}

		void PolygonShape::render()
		{
			for (unsigned int i = 0; i < transformed.size(); i++)
			{
				int j = i + 1 == transformed.size() ? 0 : i + 1;
				Math::Vector2 p1 = transformed[i];
				Math::Vector2 p2 = transformed[j];
				Renderer::DrawLine(p1, p2, getColor());
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

		void PolygonShape::applyGravity()
		{
			applyForce(getGravit() * getMass());

			float factor = 1 / transformed.size();

			for (unsigned int i = 0; i < transformed.size(); i++)
			{
				Math::Vector2 radius = transformed[i] - getPosition();
				applyForce(getGravit() * getInertia() * factor, radius);
			}
		}

		void PolygonShape::calculateUnits()
		{
			int n = transformed.size();
			Math::Vector2 center = getPosition();

			Material material = getMaterial();

			float totalMass = 0;
			float totalInertia = 0;

			for (unsigned int i = 0; i < n; i++)
			{
				Math::Vector2 p1 = transformed[i];
				Math::Vector2 p2 = transformed[(i + 1) % n];

				Math::Vector2 midpoint;
				float heightSqr = Math::distPointToLine(center, p1, p2, &midpoint);

				Math::Vector2 triangleCenter1 = (center + p1 + midpoint) / 3;
				Math::Vector2 triangleCenter2 = (center + p2 + midpoint) / 3;

				float b1 = Math::pythagoreanSolve(p1, midpoint);
				float b2 = Math::pythagoreanSolve(p2, midpoint);

				float area1 = sqrt(heightSqr + b1) / 2;
				float area2 = sqrt(heightSqr + b2) / 2;

				float mass1 = area1 * material.density;
				float mass2 = area2 * material.density;

				float j1 = (mass1 / 18) * (b1 + heightSqr);
				float j2 = (mass2 / 18) * (b2 + heightSqr);

				totalMass += mass1;
				totalMass += mass2;

				totalInertia += j1 * Math::pythagoreanSolve(center, triangleCenter1);
				totalInertia += j2 * Math::pythagoreanSolve(center, triangleCenter2);
			}

			setMass(totalMass);
			setInertia(totalInertia);
		}
	}
}