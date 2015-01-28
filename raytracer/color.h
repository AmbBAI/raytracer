#ifndef _RAYTRACER_COLOR_H_
#define _RAYTRACER_COLOR_H_

#include "header.h"

namespace rt
{

struct Color32;
struct Color
{
	float a, r, g, b;
	Color(float _a, float _r, float _g, float _b);
	Color(const Color& _color);
	Color(const Color32& _color32);

	static const Color white;
	static const Color black;
};

struct Color32
{
	union
	{
		u32 argb;
		struct 
		{
			u8 b, g, r, a;
		};
	};

	Color32(u32 _argb);
	Color32(u8 _a, u8 _r, u8 _g, u8 _b);
	Color32(const Color32& _color32);
	Color32(const Color& _color);

	static const Color32 white;
	static const Color32 black;
};

}
#endif //!_RAYTRACER_COLOR_H_