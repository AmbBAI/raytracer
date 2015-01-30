#ifndef _RAYTRACER_OBJECT_H_
#define _RAYTRACER_OBJECT_H_

#include "base/ray3.h"
#include "material/material.h"

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
	Material* material = nullptr;

	virtual void Initialize() {}
	virtual const IntersectResult Intersect(const Ray3& ray) const { return IntersectResult::noHit; }
};
}

#endif //!_RAYTRACER_OBJECT_H_
