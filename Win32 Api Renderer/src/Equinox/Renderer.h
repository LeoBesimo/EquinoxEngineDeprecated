#pragma once

#include <Windows.h>
#include <stdint.h>
#include <assert.h>
#include <vector>

#include "Math/eqMath.h"

namespace eq
{
	struct Color
	{
		uint8_t red = 0, green = 0, blue = 0;
		float alpha;
		
		Color() {}

		Color(uint8_t red, uint8_t green, uint8_t blue) :
			red(red), green(green), blue(blue), alpha(1)
		{}

		Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
			red(red), green(green), blue(blue), alpha(alpha / 255.f)
		{}

	};

	struct Rect
	{
		int x, y, width, height;

		Rect(float x, float y, float width, float height) :
			x(int(x + 0.5f)), y(int(y + 0.5f)), width(int(width + 0.5f)), height(int(height + 0.5f))
		{}

	};

	struct Text
	{
		int x, y;
		int length;
		const wchar_t* text;
		Color color;
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
		BitmapBuffer buffer[2];
		Color clearColor;
		std::vector<Text> text;
		bool buffer2 = false;
		bool swappedBuffers = false;

		static float alphaScaler;

	public:
		static void setClearColor(const Color& color) { getInstance().clearColor = color; }
		static void SetPixel(int x, int y, const Color& color);
		static void FillRectangle(const Rect& rect, const Color& color);
		static void DrawRectangle(const Rect& rect, const Color& color);
		static void DrawLine(int x0, int y0, int x1, int y1, const Color& color);
		static void DrawLine(Math::Vector2 a, Math::Vector2 b, const Color& color);
		static void FillCircle(int originX, int originY, int radius, const Color& color);
		static void FillEllipse(int originX, int originY, int radiusX, int radiusY, const Color& color);
		static void DrawCircle(int originX, int originY, int radius, const Color& color);
		static void DrawCircle(Math::Vector2 position, int radius, const Color& color);
		static void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, const Color& color);
		
		static void WriteText(const wchar_t* text, int x, int y, const Color& color);

		static void swapBuffers()
		{
			getInstance().buffer2 = !getInstance().buffer2;
			getInstance().swappedBuffers = true;
		}

		static bool buffersSwapped() { return getInstance().swappedBuffers; }

	private:
		Renderer() { buffer[0] = {}; buffer[1] = {}; clearColor = Color(255, 255, 255, 255); alphaScaler = 1 / 255; }
		
		Renderer(const Renderer&) = delete;
		Renderer& operator= (const Renderer&) = delete;

		~Renderer() {}

		inline static Renderer& getInstance()
		{
			static Renderer renderer;
			return renderer;
		}

	private:
		
		static BitmapBuffer& getActiveBuffer() { return getInstance().buffer[getInstance().buffer2]; }
		static BitmapBuffer& getInactiveBuffer() 
		{ 
			return getInstance().buffer[!getInstance().buffer2];
		}

		inline static void setWindowHandle(HWND windowHandle) { getInstance().windowHandle = windowHandle; }
		static void getWindowDimenstions(int* outWidth, int* outHeight);
		static void resizeFrameBuffer(int width, int height);
		static void copyBufferToWindow(HDC deviceContext, int windowWidth, int windowHeight);
		static void clear();

		static void plotLineLow(int x0, int y0, int x1, int y1, const Color& color);
		static void plotLineHigh(int x0, int y0, int x1, int y1, const Color& color);

		static Color ColorFromUInt(uint32_t color);
		static uint32_t UIntFromColor(Color color);
		static uint32_t BlendColor(Color original, Color Background);
		static uint32_t BlendColor(Color original, uint32_t background);
	};
}