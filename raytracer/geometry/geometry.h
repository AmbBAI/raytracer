#ifndef _RAYTRACER_GEOMETRIES_H_
#define _RAYTRACER_GEOMETRIES_H_

#include "base/ray3.h"
#include "material/material.h"
#include "geometry/intersect_result.h"
#include "base/aabb_tree.h"

namespace rt
{

struct Geometry
{
	Material* material = nullptr;
	AABB aabb;

	virtual void Initialize() {}
	virtual const IntersectResult Intersect(const Ray3& ray) const { return IntersectResult::noHit; }
};
}

#endif //!_RAYTRACER_GEOMETRIES_H_
