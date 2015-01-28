#include "color.h"

namespace rt
{

const Color Color::white = Color(1.f, 1.f, 1.f, 1.f);
const Color Color::black = Color(1.f, 0.f, 0.f, 0.f);

Color::Color(float _a, float _r, float _g, float _b)
	: a(_a), r(_r), g(_g), b(_b)
{
}

Color::Color(const Color& _color)
	: a(_color.a), r(_color.r), g(_color.g), b(_color.b)
{
}

Color::Color(const Color32& _color32)
	: a(_color32.a / 255.f)
	, r(_color32.r / 255.f)
	, g(_color32.g / 255.f)
	, b(_color32.b / 255.f)
{
}


const Color32 Color32::white = Color32(0xffffffff);
const Color32 Color32::black = Color32(0xff000000);

Color32::Color32(u32 _argb)
	: argb(_argb)
{
}

Color32::Color32(unsigned char _a, unsigned char _r, unsigned char _g, unsigned char _b)
	: a(_a), r(_r), g(_g), b(_b)
{
	//printf("%x %x %x %x %x - %d\n", a, r, g, b, argb, sizeof(Color));
}

Color32::Color32(const Color32& _color32)
	: argb(_color32.argb)
{
}

Color32::Color32(const Color& _color)
	: a((u8)(_color.a * 0xff))
	, r((u8)(_color.r * 0xff))
	, g((u8)(_color.g * 0xff))
	, b((u8)(_color.b * 0xff))
{
}

}