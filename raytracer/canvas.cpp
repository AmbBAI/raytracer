#include "canvas.h"
#include "color.h"

namespace rt
{

Canvas::Canvas(HWND hWnd, int width, int height)
{
	this->hWnd = hWnd;
	this->hDC = ::GetDC(hWnd);
	this->width = width;
	this->height = height;
}

Canvas::~Canvas()
{
	::ReleaseDC(this->hWnd, this->hDC);
}

bool Canvas::SetPixel(int x, int y, const Color& color)
{
	if (this->hDC == INVALID_HANDLE_VALUE) return false;
	if (x < 0 || x >= width) return false;
	if (y < 0 || y >= height) return false;

	

	COLORREF ret = ::SetPixel(this->hDC, x, y, (COLORREF)(color.argb & 0x00ffffff));
	return true;
}

int Canvas::GetWidth()
{
	return width;
}

int Canvas::GetHeight()
{
	return height;
}

}