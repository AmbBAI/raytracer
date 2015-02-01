#ifndef _RAYTRACER_CUBOID_H_
#define _RAYTRACER_CUBOID_H_

#include "base/header.h"
#include "base/vector3.h"
#include "base/ray3.h"
#include "geometry.h"

namespace rt
{

struct Cuboid : Geometry
{
	Cuboid(const Vector3& _position,
		const Vector3& _up, const Vector3& _front,
		float _length, float _width, float _height);

	virtual void Initialize();
	virtual const IntersectResult Intersect(const Ray3& ray) const;

	Vector3 position = Vector3::zero;
	Vector3 up = Vector3::up;
	Vector3 right = Vector3::right;
	Vector3 front = Vector3::front;
	Vector3 down = Vector3::down;
	Vector3 left = Vector3::left;
	Vector3 back = Vector3::back;
	float length = 1.f;
	float width = 1.f;
	float height = 1.f;

private:
	const Vector3 TranslateToLocal(const Vector3& v) const;
	bool CheckPoint(float x, float y, float z) const;
	bool CheckPoint(const Vector3& v) const;

	float halfWidth = 0.5f;
	float halfLength = 0.5f;
	float halfHeight = 0.5f;
};


}

#endif //!_RAYTRACER_CUBOID_H_
