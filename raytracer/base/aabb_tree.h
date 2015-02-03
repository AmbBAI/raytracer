#ifndef _RAYTRACER_AABBTREE_H_
#define _RAYTRACER_AABBTREE_H_

#include "header.h"
#include "vector3.h"
#include "ray3.h"

namespace rt
{

struct AABB
{
	float minX, maxX;
	float minY, maxY;

	bool Intersect(const Ray3& ray);
};

struct AABBNode
{
	AABB aabb;
	std::vector<Geometry*> objs;

	AABBNode* left = nullptr;
	AABBNode* right = nullptr;
};

struct AABBTree
{
	AABBTree(const std::vector<Geometry*>& objs, int depth);
	AABBTree(const std::vector<Geometry*>& objs, const AABB& aabb, int depth);

	std::vector<AABBNode> nodes;
	int depth;
};

}

#endif //!_RAYTRACER_AABBTREE_H_
