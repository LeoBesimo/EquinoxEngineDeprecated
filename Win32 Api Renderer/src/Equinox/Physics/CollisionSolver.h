#pragma once

#include "CollisionDetector.h"

namespace eq 
{
	namespace Physics
	{
		class CollisionSolver
		{
		public:
			CollisionSolver() {};
			
			void resolveDynamic(Manifold m);
		};
	}
}