#ifndef _RAYTRACER_POLYGON_H_
#define _RAYTRACER_POLYGON_H_

#include "base/header.h"
#include "base/vector3.h"
#include "base/ray3.h"
#include "base/aabb_tree.h"
#include "base/matrix4x4.h"
#include "triangle.h"
#include "geometry.h"


namespace rt
{

struct Polygon : Geometry
{
	Polygon(const char* objFile);
	Polygon(const std::vector<Triangle>& triangles);

	virtual void Initialize();
	virtual const IntersectResult Intersect(const Ray3& ray) const;

	void SetTransform(const Vector3& position, const Vector3& rotation, const Vector3& scale);

	std::vector<Triangle> triangles;
	std::vector<Triangle*> triangles_ptr;

	AABBTree aabbTree;

	Matrix4x4 transform;
	Matrix4x4 invTransform;

};


}

#endif //!_RAYTRACER_POLYGON_H_
