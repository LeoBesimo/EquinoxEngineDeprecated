#include "Game.h"

namespace eq
{
	Game::Game()
	{
		windowTitle = L"Equinox Application";
		windowWidth = 1920;
		windowHeight = 1080;
	}

	Game::~Game()
	{

	}

	LRESULT CALLBACK WindowCallback(
		HWND windowHandle,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	)
	{
		LRESULT result = 0;

		switch (message)
		{
		case WM_CLOSE:
		{
			Game::getInstance().running = false;
			OutputDebugString(L"Window close\n");
		}break;

		case WM_DESTROY:
		{
			Game::getInstance().running = false;
			OutputDebugString(L"window destroy\n");
		}break;

		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			uint32_t VKCode = wParam;
			bool wasDown = (lParam & (1 << 30)) != 0;
			bool isDown = (lParam & (1 << 31)) == 0;

			Input::processKeyboardInput(VKCode, wasDown, isDown);

		}break;

		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
		{
			Input::processMouseInput(wParam, lParam);
		}break;

		case WM_MOUSEMOVE:
		{
			Input::updateMousePosition(lParam);
		}break;

		case WM_PAINT:
		{
			OutputDebugString(L"window paint\n");

			PAINTSTRUCT paint;
			HDC deviceContext = BeginPaint(windowHandle, &paint);

			int width, height;
			Renderer::getWindowDimenstions(&width, &height);

			Renderer::copyBufferToWindow(deviceContext, width, height);

			EndPaint(windowHandle, &paint);
		}break;

		default:
			result = DefWindowProc(windowHandle, message, wParam, lParam);
		}

		return result;
	}

	void Game::startWindow()
	{
		Renderer::resizeFrameBuffer(windowWidth, windowHeight);

		const wchar_t* className = L"Equinox Window";

		WNDCLASS windowClass = {};

		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = WindowCallback;
		windowClass.hInstance = hInstance;
		windowClass.lpszClassName = className;

		if (!RegisterClass(&windowClass))
		{
			OutputDebugString(L"Failed to Register Window Class\n");
		}

		windowHandle = CreateWindowEx(
			0,
			className,
			windowTitle.c_str(),
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowWidth,
			windowHeight,
			0,
			0,
			hInstance,
			0
		);

		if (windowHandle)
		{
			OutputDebugString(L"Game Init\n");
			running = true;

			Renderer::setWindowHandle(windowHandle);

			LARGE_INTEGER cpuFrequency;
			QueryPerformanceFrequency(&cpuFrequency);

			LARGE_INTEGER lastCounter;
			QueryPerformanceCounter(&lastCounter);

			while (running)
			{

				LARGE_INTEGER currentCounter;
				QueryPerformanceCounter(&currentCounter);

				int64_t counterElapsed = currentCounter.QuadPart - lastCounter.QuadPart;

				float delta = (float)counterElapsed / (float)cpuFrequency.QuadPart;

				lastCounter = currentCounter;

				MSG message;
				while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
				{
					if (message.message == WM_QUIT)
					
						running = false;
					TranslateMessage(&message);
					DispatchMessage(&message);

				}

				Renderer::clear();
			
				getInstance().update(delta);

				HDC deviceContext = GetDC(windowHandle);

				int width, height;
				Renderer::getWindowDimenstions(&width, &height);

				Renderer::copyBufferToWindow(deviceContext, width, height);

				ReleaseDC(windowHandle, deviceContext);
				
			}
		}
		else
		{
			OutputDebugString(L"Failed to Create Window\n");
			return;
		}
	}
}