#ifndef _RAYTRACER_VECTOR3_H_
#define _RAYTRACER_VECTOR3_H_

#include "header.h"

namespace rt
{

struct Vector3
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	Vector3() = default;
	Vector3(float _x, float _y, float _z);
	Vector3(const Vector3& v);

	float Length() const;
	float SqrLength() const;
	const Vector3 Normalize() const;
	const Vector3 Negate() const;
	const Vector3 Add(const Vector3& v) const;
	const Vector3 Subtract(const Vector3& v) const;
	const Vector3 Multiply(float f) const;
	const Vector3 Divide(float f) const;
	float Dot(const Vector3& v) const;
	const Vector3 Cross(const Vector3& v) const;

	static const Vector3 zero;
	static const Vector3 one;
	static const Vector3 front;
	static const Vector3 up;
	static const Vector3 right;
	static const Vector3 back;
	static const Vector3 down;
	static const Vector3 left;
};

}

#endif //!_RAYTRACER_VECTOR3_H_