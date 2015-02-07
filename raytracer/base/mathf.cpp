#include "mathf.h"

namespace rt
{

const float Mathf::epsilon = FLT_EPSILON;
const float Mathf::inifinity = FLT_MAX;
const float Mathf::PI = (float)M_PI;
const float Mathf::deg2rad = (float)M_PI / 180.0f;
const float Mathf::rad2deg = 180.0f / (float)M_PI;

float Mathf::Abs(float f)
{
	return ::fabs(f);
}
float Mathf::Sign(float f)
{
	return f < 0.f ? -1.f : 1.f;
}
bool Mathf::Approximately(float a, float b)
{
	return Mathf::Abs(a - b) < Mathf::epsilon;
}

float Mathf::Floor(float f)
{
	return ::floor(f);
}
int Mathf::FloorToInt(float f)
{
	return (int)(Mathf::Floor(f) + Mathf::epsilon);
}
float Mathf::Ceil(float f)
{
	return ::ceil(f);
}
int Mathf::CeilToInt(float f)
{
	return (int)(Mathf::Ceil(f) + Mathf::epsilon);
}
float Mathf::Round(float f)
{
	return ::round(f);
}
int Mathf::RoundToInt(float f)
{
	return (int)(Mathf::Round(f) + Mathf::epsilon);
}

float Mathf::Clamp(float value, float min, float max)
{
	return value > max ? max : Mathf::Max(value, min);
}

int Mathf::Clamp(int value, int min, int max)
{
	return value > max ? max : (value < min ? min : value);
}

float Mathf::Clamp01(float value)
{
	return Mathf::Clamp(value, 0.f, 1.f);
}

float Mathf::Min(float a, float b)
{
	return ::fmin(a, b);
}
float Mathf::Min(const float* values, int count) 
{
	if (values == nullptr) return 0.f;
	if (count <= 0) return 0.f;

	return *std::min_element(values, values + count);
}
float Mathf::Min(const std::vector<float>& values)
{
	return *std::min_element(values.begin(), values.end());
}
float Mathf::Max(float a, float b)
{
	return ::fmax(a, b);
}
float Mathf::Max(const float* values, int count)
{
	if (values == nullptr) return 0.f;
	if (count <= 0) return 0.f;

	return *std::max_element(values, values + count);
}
float Mathf::Max(const std::vector<float>& values)
{
	return *std::max_element(values.begin(), values.end());
}

float Mathf::Sin(float f)
{
	return ::sin(f);
}
float Mathf::Cos(float f)
{
	return ::cos(f);
}
float Mathf::Tan(float f)
{
	return ::tan(f);
}
float Mathf::Asin(float f)
{
	return ::asin(f);
}
float Mathf::Acos(float f)
{
	return ::acos(f);
}
float Mathf::Atan(float f)
{
	return ::atan(f);
}
float Mathf::Atan2(float y, float x)
{
	return ::atan2(y, x);
}

float Mathf::Sqrt(float value)
{
	return ::sqrt(value);
}

float Mathf::Pow(float f, float p)
{
	return ::pow(f, p);
}

float Mathf::Exp(float f)
{
	return ::exp(f);
}

float Mathf::Log(float f)
{
	return ::log(f);
}

float Mathf::Log10(float f)
{
	return ::log10(f);
}

bool Mathf::IsPowerOfTwo(int value)
{
	if (value <= 0) return false;
	return (value & (value - 1)) == 0;
}

int Mathf::NextPowerOfTwo(int value)
{
	if (value <= 0) return 1;
	if (Mathf::IsPowerOfTwo(value)) return value << 1;

	--value;
	value |= value >> 1;
	value |= value >> 2;
	value |= value >> 4;
	value |= value >> 8;
	value |= value >> 16;
	++value;
	return value;
}

}
