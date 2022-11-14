#include "Equinox/Equinox.h"

equinoxAppEntryPoint
{

	//game init

	eq::Game::setWindowProperties(L"Test Window", 1280,720);

	eq::Physics::BoxShape shape(eq::Math::Vector2(400, 400), 0.f, eq::Physics::Materials::SUPERBALL, eq::Math::Matrix2x2(20, 0, 0, 20));
	shape.setOmega(eq::Math::HALF_PI);

	eq::Physics::PolygonShape poly(eq::Math::Vector2(600, 400), 0.f, 7, eq::Physics::Materials::SUPERBALL, eq::Math::Matrix2x2(40, 0, 0, 40));
	poly.setOmega(-eq::Math::QUARTER_PI);

	eq::Physics::CircleShape circle(eq::Math::Vector2(400, 200), 0.f, 30, eq::Physics::Materials::SUPERBALL);
	circle.setVelocity(eq::Math::Vector2(30, 0));
	circle.setOmega(eq::Math::PI);

	eq::Game::setGameUpdate([&](float delta)
	{
		/*wchar_t charBuffer[256];
		swprintf(charBuffer, 256, L"Framerate: %f\n", 1/delta);
		OutputDebugString(charBuffer);*/

		static int frames = 0;
		static float timePassed = 0.f;

		frames++;
		timePassed += delta;

		if (timePassed >= 1.0f)
		{
			/*swprintf(charBuffer, 256, L"FPS: %d\n", frames);*/
			//OutputDebugString(charBuffer);

			frames = 0;
			timePassed -= 1.0f;


		}

		eq::Input::Position mouse = eq::Input::getMousePosition();
		//shape.setPosition(eq::Math::Vector2(mouse.x, mouse.y));

		//eq::Renderer::DrawLine(eq::Game::getWindowWidth() / 2, eq::Game::getWindowHeight() / 2, mouse.x, mouse.y, eq::Color(255, 0, 0));
		poly.update(delta);
		poly.render();

		shape.update(delta);
		shape.render();

		circle.update(delta);
		circle.render();
		
	}
	);

	eq::Renderer::setClearColor(eq::Color(56,56,56));

	eq::Game::start();
	//game destroy

	return 0;
}