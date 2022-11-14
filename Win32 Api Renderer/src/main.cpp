#include "Equinox/Equinox.h"

equinoxAppEntryPoint
{

	//game init

	eq::Game::setWindowProperties(L"Test Window", 1280,720);

	//game update
	float x = 200, y = 200;
	float speed = 100;

	eq::Game::setGameUpdate([&](float delta)
	{
		wchar_t charBuffer[256];
		swprintf(charBuffer, 256, L"Framerate: %f\n", 1/delta);
		OutputDebugString(charBuffer);

		/*swprintf(charBuffer, 256, L"Delta: %f\n", 1 / delta);
		OutputDebugString(charBuffer);*/

		static int frames = 0;
		static float timePassed = 0.f;

		frames++;
		timePassed += delta;

		if (timePassed >= 1.0f)
		{
			swprintf(charBuffer, 256, L"FPS: %d\n", frames);
			//OutputDebugString(charBuffer);

			frames = 0;
			timePassed -= 1.0f;
		}

		if (eq::Input::isKeyPressed(EQ_W)) y -= speed * delta;
		if (eq::Input::isKeyPressed(EQ_S)) y += speed * delta;
		if (eq::Input::isKeyPressed(EQ_A)) x -= speed * delta;
		if (eq::Input::isKeyPressed(EQ_D)) x += speed * delta;

		if (eq::Input::wasKeyHit(EQ_E)) speed = 200;
		if (eq::Input::wasKeyHit(EQ_Q)) speed = 100;

		eq::Renderer::DrawRectangle(eq::Rect(x,y,200,200), { 255,255,0 });

		eq::Input::Position mousePos = eq::Input::getMousePosition();

		eq::Renderer::DrawTriangle(200, 200, 350, 350, mousePos.x, mousePos.y, { 0,255,0 });

		swprintf(charBuffer, 256, L"%d : %d\n", mousePos.x, mousePos.y);
		//OutputDebugString(charBuffer);
		
	}
	);

	eq::Renderer::setClearColor({ 200,120,20 });

	eq::Game::start();
	//game destroy

	return 0;
}