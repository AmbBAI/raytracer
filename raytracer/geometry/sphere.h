#ifndef _RAYTRACER_SPHERE_H_
#define _RAYTRACER_SPHERE_H_

#include "base/header.h"
#include "base/vector3.h"
#include "base/ray3.h"
#include "geometry.h"

namespace rt
{

struct Sphere : Geometry
{
	Sphere(const Vector3& _center, float _radius);

	virtual void Initialize();
	virtual const IntersectResult Intersect(const Ray3& ray) const;

private:
	Vector3 center = Vector3::zero;
	float radius = 1.f;

	float sqrRadius = 1.f;
};


}

#endif //!_RAYTRACER_SPHERE_H_
