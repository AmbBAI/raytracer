#ifndef _RAYTRACER_AABBTREE_H_
#define _RAYTRACER_AABBTREE_H_

#include "base/header.h"
#include "base/vector3.h"
#include "base/ray3.h"
#include "base/aabb.h"
#include "geometry/geometry.h"
#include "geometry/intersect_result.h"

namespace rt
{

struct Geometry;
struct AABBNode
{
	AABB aabb;
	std::vector<Geometry*> objs;

	int left = -1;
	int right = -1;
};

struct AABBTree
{
	AABBTree() = default;
	AABBTree(const std::vector<Geometry*>& objs, int depth);

	void BuildTree(const std::vector<Geometry*>& objs, int depth, int idx);

	const IntersectResult Intersect(const Ray3& ray) const;
	const IntersectResult NodeIntersect(const Ray3& ray, const AABBNode& node) const;

	std::vector<AABBNode> nodes;
	int auto_idx = 0;
};

}

#endif //!_RAYTRACER_AABBTREE_H_
