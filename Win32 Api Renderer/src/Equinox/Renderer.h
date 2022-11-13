#pragma once

#include <Windows.h>
#include <stdint.h>

namespace eq
{
	struct RGBColor
	{
		uint8_t red, green, blue;
	};

	struct Rect
	{
		int x, y, width, height;
	};

	class Renderer
	{
		friend LRESULT CALLBACK WindowCallback(
			HWND windowHandle,
			UINT message,
			WPARAM wParam,
			LPARAM lParam
		);

		friend class Game;

		struct BitmapBuffer
		{
			int width, height;
			BITMAPINFO info;
			void* memory;
			int pitch; // in bytes;
		};

	private:
		static const int bytesPerPixel = 4;

		HWND windowHandle = 0;
		BitmapBuffer buffer;
		RGBColor clearColor;

	public:
		inline static void setClearColor(const RGBColor& color) { getInstance().clearColor = color; }
		static void setPixel(int x, int y, const RGBColor& color);
		static void fillRectanglge(const Rect& rect, const RGBColor& color);

	private:
		Renderer() { buffer = {}; clearColor = { 255, 255, 255 }; }
		
		Renderer(const Renderer&) = delete;
		Renderer& operator= (const Renderer&) = delete;

		~Renderer() {}

		inline static Renderer& getInstance()
		{
			static Renderer renderer;
			return renderer;
		}

	private:
		inline static void setWindowHandle(HWND windowHandle) { getInstance().windowHandle = windowHandle; }
		static void getWindowDimenstions(int* outWidth, int* outHeight);
		static void resizeFrameBuffer(int width, int height);
		static void copyBufferToWindow(HDC deviceContext, int windowWidth, int windowHeight);
		static void clear();
	};
}