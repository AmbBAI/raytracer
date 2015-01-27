#ifndef _RAYTRACER_COLOR_H_
#define _RAYTRACER_COLOR_H_

namespace rt
{

struct Color
{
	unsigned argb = 0xff000000;

	Color();
	Color(int a, int r, int g, int b);
	Color(const Color& color);

	static const Color white;
	static const Color black;
};

}
#endif //!_RAYTRACER_COLOR_H_