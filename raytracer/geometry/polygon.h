#ifndef _RAYTRACER_MESH_H_
#define _RAYTRACER_MESH_H_

#include "base/header.h"
#include "base/vector3.h"
#include "base/ray3.h"
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

	std::vector<Triangle> triangles;
	std::vector<Triangle*> triangles_ptr;
};


}

#endif //!_RAYTRACER_CUBOID_H_
