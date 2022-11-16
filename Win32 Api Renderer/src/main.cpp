#include "Equinox/Equinox.h"

equinoxAppEntryPoint
{
	eq::Game::setWindowProperties(L"Test Window", 800,800);

	eq::Physics::BoxShape shape(eq::Math::Vector2(400, 400), 0.f, eq::Physics::Materials::SUPERBALL, eq::Math::Matrix2x2(20, 0, 0, 20));
	shape.setOmega(eq::Math::HALF_PI);
	shape.setGravity(eq::Math::Vector2(0, 50));
	shape.setColor(eq::Color(255, 0, 0));

	eq::Physics::PolygonShape poly(eq::Math::Vector2(600, 400), 0.f, 7, eq::Physics::Materials::SUPERBALL, eq::Math::Matrix2x2(40, 0, 0, 40));
	poly.setOmega(-eq::Math::QUARTER_PI);

	eq::Physics::CircleShape circle(eq::Math::Vector2(400, 200), 0.f, 30, eq::Physics::Materials::SUPERBALL);
	circle.setVelocity(eq::Math::Vector2(80, 0));
	circle.setOmega(eq::Math::PI);

	eq::Physics::CircleShape circle2(eq::Math::Vector2(600, 200), 0.f, 30, eq::Physics::Materials::SUPERBALL);

	eq::Physics::CollisionDetector detector;
	eq::Physics::CollisionSolver solver;

	eq::Game::setGameUpdate([&](float delta)
	{
		wchar_t charBuffer[256];
		swprintf(charBuffer, 256, L"Framerate: %f\n", 1/delta);
		OutputDebugString(charBuffer);

		eq::Math::Vector2 mouse;
		eq::Input::getMousePosition(&mouse);

		//circle2.setPosition(mouse);

		//shape.setPosition(mouse);

		eq::Physics::Manifold manifold = detector.detectCollision(&circle, &circle2);
		if (manifold.colliding)
		{
			circle.setColor(eq::Color(255, 0, 0));
			circle2.setColor(eq::Color(255, 0, 0));
			solver.resolveDynamic(manifold);

			//OutputDebugString(L"Colliding");
		}
		else
		{
			circle.setColor(eq::Color(255, 0, 255));
			circle2.setColor(eq::Color(255, 0, 255));
		}


	/*	eq::Renderer::DrawLine(1280, 0, 1280, 720, eq::Color(0,255,255));
		eq::Renderer::DrawLine(0, 720, 1280, 720, eq::Color(0,255,255));
		eq::Renderer::DrawLine(0, 0, 0, 720, eq::Color(0,255,255));
		eq::Renderer::DrawLine(0, 0, 1280, 0, eq::Color(0,255,255));*/

		poly.update(delta);
		poly.render();

		shape.update(delta);
		shape.render();

		circle.update(delta);
		circle.render();
		
		circle2.update(delta);
		circle2.render();

	}
	);

	eq::Renderer::setClearColor(eq::Color(56,56,56));

	eq::Game::start();
	//game destroy

	return 0;
}
