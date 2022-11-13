#include "Equinox/Equinox.h"

equinoxAppEntryPoint
{

	//game init

	//game update

	int x = 200, y = 200;

	eq::Game::setGameUpdate([&](float delta)
	{
		wchar_t charBuffer[256];
		swprintf(charBuffer, 256, L"Framerate: %f\n", 1/delta);
		OutputDebugString(charBuffer);

		if (eq::Input::isKeyPressed(EQ_W)) y -= 5;
		if (eq::Input::isKeyPressed(EQ_S)) y += 5;
		if (eq::Input::isKeyPressed(EQ_A)) x -= 5;
		if (eq::Input::isKeyPressed(EQ_D)) x += 5;

		eq::Renderer::fillRectanglge({ x,y,300,300 }, { 255,255,0 });

		if (eq::Input::isMouseButtonPressed(EQ_MOUSE_MIDDLE)) OutputDebugString(L"Middle button pressed\n");
		eq::Input::Position position = eq::Input::getMousePosition();
		swprintf(charBuffer, 256, L"%d, %d\n", position.x, position.y);
		OutputDebugString(charBuffer);
	}
	);

	eq::Renderer::setClearColor({ 200,120,20 });

	eq::Game::start();
	//game destroy

	return 0;
}