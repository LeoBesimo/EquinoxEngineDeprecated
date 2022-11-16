#include "CollisionSolver.h"

namespace eq
{
	namespace Physics
	{
		void CollisionSolver::resolveDynamic(Manifold m)
		{
			Shape* bodyA = m.bodyA;
			Shape* bodyB = m.bodyB;

			Math::Vector2 normal = m.normal;
			Math::Vector2 contact = m.contact;

			Math::Vector2 ra = contact - bodyA->getPosition();
			Math::Vector2 rb = contact - bodyB->getPosition();

			Math::Vector2 raPerp(-ra.y, ra.x);
			Math::Vector2 rbPerp(-rb.y, rb.x);

			Math::Vector2 velB = bodyB->getVelocity();
			Math::Vector2 velA = bodyA->getVelocity();

			Math::Vector2 rv = (velB + rbPerp * bodyB->getOmega()) - (velA + raPerp * bodyA->getOmega());
			
			float contactVelMag = Math::dot(rv, normal);
			if (contactVelMag > 0)
				return;

			float e = min(bodyA->getMaterial().restitution, bodyB->getMaterial().restitution);

			float denom1 = bodyA->getInvMass() + bodyB->getInvMass();
			float denom2 = Math::square(Math::dot(raPerp, normal)) * bodyA->getInvInertia();
			float denom3 = Math::square(Math::dot(rbPerp, normal)) * bodyB->getInvInertia();
			
			float j = -(1 + e) * contactVelMag;
			j /= (denom1 + denom2 + denom3);

			Math::Vector2 impulse = normal * j;
			
			bodyA->setVelocity(bodyA->getVelocity() - impulse * bodyA->getInvMass());
			bodyB->setVelocity(bodyB->getVelocity() + impulse * bodyB->getInvMass());

			float omegaA = bodyA->getOmega() - Math::cross(ra, impulse) * bodyA->getInvInertia();
			float omegaB = bodyB->getOmega() + Math::cross(rb, impulse) * bodyB->getInvInertia();

			bodyA->setOmega(omegaA);
			bodyB->setOmega(omegaB);
		}
	}
}