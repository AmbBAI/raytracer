#ifndef _RAYTRACER_INTERSECT_RESULT_H_
#define _RAYTRACER_INTERSECT_RESULT_H_

#include "base/header.h"
#include "base/vector3.h"

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

}

#endif //!_RAYTRACER_INTERSECT_RESULT_H_
