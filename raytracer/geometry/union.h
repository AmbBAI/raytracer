#ifndef _RAYTRACER_UNION_H_
#define _RAYTRACER_UNION_H_

#include "base/header.h"
#include "base/vector3.h"
#include "base/ray3.h"
#include "geometry.h"

namespace rt
{

struct Union : Geometry
{
	Union(Geometry* g1, Geometry* g2);
	Union(Geometry* g1, Geometry* g2, Geometry* g3);
	Union(Geometry* g1, Geometry* g2, Geometry* g3, Geometry* g4);
	//Union(Geometry* g[], int count);

	virtual void Initialize();
	virtual const IntersectResult Intersect(const Ray3& ray) const;

	std::vector<Geometry*> geometries;
};


}

#endif //!_RAYTRACER_UNION_H_
