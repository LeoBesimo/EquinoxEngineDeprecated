#include "Equinox/Equinox.h"

equinoxAppEntryPoint
{
	eq::Game::setWindowProperties(L"Test Window", 1000,800);

	eq::Physics::PhysicsWorld world(eq::Math::Vector2(eq::Game::getWindowWidth(), eq::Game::getWindowHeight()));

	eq::Physics::BoxShape* shape = world.addBox(eq::Math::Vector2(400, 400), 0.f, eq::Physics::Materials::SUPERBALL, eq::Math::Vector2(20, 20));
	shape -> setColor(eq::Color(255, 0, 0));

	eq::Physics::PolygonShape* poly3 = world.addPolygon(eq::Math::Vector2(400, 200), 0.f, 5, eq::Physics::Materials::SUPERBALL, eq::Math::Matrix2x2(30,0,0,30));

	eq::Physics::BoxShape* box = world.addBox(eq::Math::Vector2(400, 600), 0.f, eq::Physics::Materials::SUPERBALL, eq::Math::Vector2(30, 20));
	//box->setVelocity(eq::Math::Vector2(0, -50));
	box->setOmega(eq::Math::QUARTER_PI);

	eq::Physics::PolygonShape* poly = world.addPolygon(eq::Math::Vector2(600, 600), 0.f, 7, eq::Physics::Materials::SUPERBALL, eq::Math::Matrix2x2(40, 0, 0, 40));
	eq::Physics::PolygonShape* poly2 = world.addPolygon(eq::Math::Vector2(700, 600), 0.f, 3, eq::Physics::Materials::SUPERBALL, eq::Math::Matrix2x2(40, 0, 0, 40));
	//poly2->setVelocity(eq::Math::Vector2(-20, 0));
	poly->setOmega(eq::Math::QUARTER_PI);

	eq::Physics::CircleShape* circle = world.addCircle(eq::Math::Vector2(400, 200), 0.f, 30, eq::Physics::Materials::SUPERBALL);
	//circle->setVelocity(eq::Math::Vector2(80, 0));
	circle->setOmega(eq::Math::PI);

	eq::Physics::BoxShape* floor = world.addBox(eq::Math::Vector2(500, 800), 0.f, eq::Physics::Materials::STATIC, eq::Math::Vector2(800, 50));
	eq::Physics::PolygonShape* polygon = new eq::Physics::PolygonShape(eq::Math::Vector2(300, 300), 0.f, 6, eq::Physics::Materials::SUPERBALL, eq::Math::Matrix2x2(30, 0, 0, 30));
	polygon->setColor(eq::Color(255, 0, 0));

	world.addBody(polygon);

	eq::Game::setGameUpdate([&](float delta)
	{
		/*wchar_t charBuffer[256];
		swprintf(charBuffer, 256, L"Framerate: %f\n", 1/delta);
		OutputDebugString(charBuffer);*/

		eq::Math::Vector2 mouse;
		eq::Input::getMousePosition(&mouse);

		if (eq::Input::wasKeyHit(EQ_SPACE)) world.setWorldGravity(eq::Math::Vector2(0, 100));
		if (eq::Input::wasKeyHit(EQ_W)) world.addPolygon(mouse, 0.f, 6, eq::Physics::Materials::SUPERBALL, eq::Math::Matrix2x2(30, 0, 0, 30));

		world.update(delta);
		world.render();

		wchar_t charBuffer[64];
		swprintf(charBuffer, 64,L"Framerate: %d", int(1 / delta + 0.5f));
		eq::Renderer::WriteText(charBuffer, 10, 10, eq::Color(255,0,255));


		eq::Renderer::WriteText(L"Test", 200, 200, eq::Color(255,0,255));
	}
	);

	eq::Renderer::setClearColor(eq::Color(56,56,56));

	eq::Game::start();

	return 0;
}
