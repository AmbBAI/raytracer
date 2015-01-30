#ifndef _RAYTRACER_GEOMETRIES_H_
#define _RAYTRACER_GEOMETRIES_H_

#include "base/ray3.h"
#include "material/material.h"

namespace rt
{

struct Geometry;
struct IntersectResult
{
	const Geometry* geometry = nullptr;
	float distance = 0;
	Vector3 position = Vector3::zero;
	Vector3 normal = Vector3::zero;

	static const IntersectResult noHit;
};

__declspec(selectany) const IntersectResult IntersectResult::noHit = IntersectResult();

struct Geometry
{
	Material* material = nullptr;

	virtual void Initialize() {}
	virtual const IntersectResult Intersect(const Ray3& ray) const { return IntersectResult::noHit; }
};
}

#endif //!_RAYTRACER_GEOMETRIES_H_
