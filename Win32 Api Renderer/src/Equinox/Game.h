#pragma once

#include <Windows.h>

#include <string>
#include <functional>
#include <thread>

#include "Renderer.h"
#include "Input.h"

namespace eq
{
	class Game
	{
		friend LRESULT CALLBACK WindowCallback(
			HWND windowHandle,
			UINT message,
			WPARAM wParam,
			LPARAM lParam
		);

	private:
		HINSTANCE hInstance;
		HWND windowHandle;
		bool running = false;

		std::wstring windowTitle;
		int windowWidth;
		int windowHeight;

		std::function<void(float delta)> update;
		float secondsPerFrame = 1.f / 240.f;

	public:
		Game();

		Game(const Game&) = delete;
		Game& operator= (const Game&) = delete;
	
		~Game();

		inline static Game& getInstance()
		{
			static Game game;
			return game;
		}

		inline static void start() 
		{
			getInstance().startWindow();
		}

		inline static void setWindowProperties(const std::wstring& title, const int& width, const int& height)
		{
			getInstance().windowTitle = title;
			getInstance().windowWidth = width + 1;
			getInstance().windowHeight = height + 1;
		}

		inline static void setGameUpdate(const std::function<void(float delta)>& update) { getInstance().update = update; }

		inline static std::wstring getWindowTitle() { return getInstance().windowTitle; }
		inline static int getWindowWidth() { return getInstance().windowWidth; }
		inline static int getWindowHeight() { return getInstance().windowHeight; }
		inline static HWND getWindowHandle() { return getInstance().windowHandle; }
		inline static bool isRunning() { return getInstance().running; }
		
	private:
		void startWindow();
	};
}