#ifndef _RAYTRACER_RAY3_H_
#define _RAYTRACER_RAY3_H_

#include "header.h"
#include "vector3.h"

namespace rt
{

struct Ray3
{
	Vector3 origin;
	Vector3 direction;

	Ray3(const Vector3& _origin, const Vector3& _direction);

	const Vector3& GetPoint(float t) const;
};


}

#endif //!_RAYTRACER_RAY3_H_
