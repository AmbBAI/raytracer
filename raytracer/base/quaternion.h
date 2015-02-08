#ifndef _RAYTRACER_QUATERNION_H_
#define _RAYTRACER_QUATERNION_H_
#include "header.h"
#include "vector3.h"

namespace rt
{
struct Quaternion
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 0.f;

	Quaternion() = default;
	Quaternion(const Vector3& eulerAngle);
	Quaternion(float _x, float _y, float _z, float _w);

	void SetEulerAngle(float _x, float _y, float _z);
	void SetEulerAngle(const Vector3& euler_angle);
	const Vector3& GetEulerAngle();

	static const Quaternion identity;
};
}

#endif //_RAYTRACER_QUATERNION_H_