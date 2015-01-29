#ifndef _RAYTRACER_OBJECT_H_
#define _RAYTRACER_OBJECT_H_

#include "base/ray3.h"

namespace rt
{

struct Object;
struct IntersectResult
{
	const Object* geometry = nullptr;
	float distance = 0;
	Vector3 position = Vector3::zero;
	Vector3 normal = Vector3::zero;

	static const IntersectResult noHit;
};

__declspec(selectany) const IntersectResult IntersectResult::noHit = IntersectResult();

struct Object
{
	virtual void Initialize() = 0;
	virtual const IntersectResult Intersect(const Ray3& ray) const = 0;
};
}

#endif //!_RAYTRACER_OBJECT_H_
