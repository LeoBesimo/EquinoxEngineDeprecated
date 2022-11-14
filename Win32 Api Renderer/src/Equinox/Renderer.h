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

		Rect(float x, float y, float width, float height) :
			x(int(x + 0.5f)), y(int(y + 0.5f)), width(int(width + 0.5f)), height(int(height + 0.5f))
		{}

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
		static void setClearColor(const RGBColor& color) { getInstance().clearColor = color; }
		static void SetPixel(int x, int y, const RGBColor& color);
		static void FillRectangle(const Rect& rect, const RGBColor& color);
		static void DrawRectangle(const Rect& rect, const RGBColor& color);
		static void DrawLine(int x0, int y0, int x1, int y1, const RGBColor& color);
		static void FillCircle(int originX, int originY, int radius, const RGBColor& color);
		static void FillEllipse(int originX, int originY, int radiusX, int radiusY, const RGBColor& color);
		static void DrawCircle(int originX, int originY, int radius, const RGBColor& color);
		static void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, const RGBColor& color);

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

		static void plotLineLow(int x0, int y0, int x1, int y1, const RGBColor& color);
		static void plotLineHigh(int x0, int y0, int x1, int y1, const RGBColor& color);
	};
}