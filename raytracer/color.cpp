#include "color.h"

namespace rt
{

Color::Color()
	: argb(0xff000000)
{

}

Color::Color(int a, int r, int g, int b)
	: argb((((((a << 8) | r) << 8) | g) << 8) | b)
{

}

Color::Color(const Color& color)
{
	argb = color.argb;
}

}