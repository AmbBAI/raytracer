#ifndef _RAYTRACER_SPHERE_H_
#define _RAYTRACER_SPHERE_H_

#include "header.h"
#include "vector3.h"
#include "ray3.h"

namespace rt
{

struct Sphere;
struct IntersectResult
{
	const Sphere* geometry = nullptr;
	float distance = 0;
	Vector3 position = Vector3::zero;
	Vector3 normal = Vector3::zero;
	
	static const IntersectResult noHit;
};

struct Sphere
{
	Vector3 center = Vector3::zero;
	float radius = 1.f;

	Sphere(const Vector3& _center, float _radius);

	void Initialize();
	const IntersectResult& Intersect(const Ray3& ray) const;

private:
	float sqrRadius = 1.f;
};


}

#endif //!_RAYTRACER_SPHERE_H_
