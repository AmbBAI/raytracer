#ifndef _RAYTRACER_TRIANGLE_H_
#define _RAYTRACER_TRIANGLE_H_

#include "base/header.h"
#include "base/vector3.h"
#include "base/ray3.h"
#include "geometry.h"

namespace rt
{

struct Triangle : Geometry
{
	Triangle(const Vector3& _v0, const Vector3& _v1, const Vector3& _v2);
	Triangle(const Vector3& _v0, const Vector3& _v1, const Vector3& _v2,
		const Vector3& _n0, const Vector3& _n1, const Vector3& _n2);

	virtual void Initialize();
	virtual const IntersectResult Intersect(const Ray3& ray) const;

	Vector3 v0;
	Vector3 v1;
	Vector3 v2;

	Vector3 n0;
	Vector3 n1;
	Vector3 n2;

	Vector3 e1;
	Vector3 e2;
};
}

#endif //!_RAYTRACER_TRIANGLE_H_
