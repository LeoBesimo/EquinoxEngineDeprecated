#pragma once

namespace eq
{
	namespace Physics
	{
		struct Material
		{
			float density;
			float restitution;
		
			Material(float density, float restitution) :
				density(density), restitution(restitution)
			{}
		};
	
		namespace Materials
		{
			static const Material SUPERBALL(1, 1);
			static const Material STATIC(0, 0);
		}

	}
}