#pragma once

namespace eq
{
	namespace Physics
	{
		struct Material
		{
			float density;
			float restitution;
			float staticFriction;
			float dynamicFriction;
		
			Material(float density, float restitution, float staticFriction, float dynamicFriction) :
				density(density), restitution(restitution), staticFriction(staticFriction), dynamicFriction(dynamicFriction)
			{}
		};
	
		namespace Materials
		{
			static const Material SUPERBALL(1, 1, 0, 0);
			static const Material STATIC(0, 1, 0, 0);
		}

	}
}