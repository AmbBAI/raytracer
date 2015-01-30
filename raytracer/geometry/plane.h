#ifndef _RAYTRACER_PLANE_H_
#define _RAYTRACER_PLANE_H_

#include "base/header.h"
#include "base/vector3.h"
#include "base/ray3.h"
#include "geometry.h"

namespace rt
{

struct Plane : Geometry
{
	Plane(const Vector3& _normal, float _d);

	virtual void Initialize();
	virtual const IntersectResult Intersect(const Ray3& ray) const;

	Vector3 position = Vector3::zero;
	Vector3 normal = Vector3::up;
	float d = 0.f;
};


}

#endif //!_RAYTRACER_PLANE_H_
