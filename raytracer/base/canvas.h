#ifndef _RAYTRACER_CANVAS_H_
#define _RAYTRACER_CANVAS_H_

#include "header.h"
#include "application.h"
#include "color.h"

namespace rt
{

class Canvas
{
public:
	Canvas(int width, int height);
	~Canvas();

public:
	bool SetPixel(int x, int y, const Color32& color);
	bool SetPixel(int x, int y, const Color& color);
	int GetWidth();
	int GetHeight();

	void BeginDraw();
	void EndDraw();

private:
	int width;
	int height;

	std::vector<u32> pixels;
};

}

#endif //!_RAYTRACER_CANVAS_H_