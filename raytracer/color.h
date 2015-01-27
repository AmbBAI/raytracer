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

	int r() const { return (argb & 0x00ff0000) >> 16; }
	int g() const { return (argb & 0x0000ff00) >> 8; }
	int b() const { return (argb & 0x000000ff) >> 0; }
	int a() const { return (argb & 0xff000000) >> 24; }

	static const Color white;
	static const Color black;
};

}
#endif //!_RAYTRACER_COLOR_H_