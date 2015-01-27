#ifndef _RAYTRACER_CANVAS_H_
#define _RAYTRACER_CANVAS_H_

#include "header.h"
#include "application.h"
#include "color.h"

namespace rt
{

class Canvas
{
	friend Application;

protected:
	Canvas(HWND hWnd, int width, int height);
	~Canvas();

public:
	bool SetPixel(int x, int y, const Color& color);
	int GetWidth();
	int GetHeight();

private:
	HWND hWnd;
	HDC hDC;
	int width;
	int height;
};

}

#endif //!_RAYTRACER_CANVAS_H_