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

	if (width > 0 && height > 0)
	{
		pixels.assign(width * height, 0);
	}
}

Canvas::~Canvas()
{
	::ReleaseDC(this->hWnd, this->hDC);
}

bool Canvas::SetPixel(int x, int y, const Color32& color)
{
	if (this->hDC == INVALID_HANDLE_VALUE) return false;
	if (x < 0 || x >= width) return false;
	if (y < 0 || y >= height) return false;

	pixels[y * width + x] = (u32)((color.b) | (((u32)color.g) << 8) | (((u32)color.r) << 16));
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

void Canvas::BeginDraw()
{

}

void Canvas::EndDraw()
{
	HDC hDCMem = CreateCompatibleDC(hDC);
	HBITMAP bitmap = ::CreateBitmap(width, height, 1, 32, &pixels[0]);
	::SelectObject(hDCMem, bitmap);
	
	::BitBlt(hDC, 0, 0, width, height, hDCMem, 0, 0, SRCCOPY);

	::DeleteDC(hDCMem);
}



}