#ifndef _RAYTRACER_AABB_H_
#define _RAYTRACER_AABB_H_

#include "base/header.h"
#include "base/vector3.h"
#include "base/ray3.h"

namespace rt
{

struct AABB
{
	float minX, maxX;
	float minY, maxY;
	float minZ, maxZ;

	float centerX, centerY, centerZ;

	AABB();
	AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
	AABB(const Vector3& p);
	AABB(const Vector3& p1, const Vector3& p2);

	const AABB Combine(const Vector3& p) const;
	const AABB Combine(const AABB& aabb) const;

	bool Intersect(const Ray3& ray) const;
};

}

#endif //!_RAYTRACER_AABB_H_
