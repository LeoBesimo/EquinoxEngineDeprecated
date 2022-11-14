#pragma once

namespace eq
{
	namespace Physics
	{
		class PhysicsWorld
		{

		private:
			PhysicsWorld();
		
		public:
			static PhysicsWorld& getInstance()
			{
				PhysicsWorld world;
				return world;
			}
		};
	}
}