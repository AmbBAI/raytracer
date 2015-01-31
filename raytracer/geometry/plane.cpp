#include "plane.h"
#include "base/mathf.h"

namespace rt
{
Plane::Plane(const Vector3& _normal, float _d)
	: normal(_normal), d(_d)
{
}

void Plane::Initialize()
{
	position = normal.Multiply(d);
}

const IntersectResult Plane::Intersect(const Ray3& ray) const
{
	float a = ray.direction.Dot(normal);
	if (a >= 0) return IntersectResult::noHit;

	float b = normal.Dot(ray.origin.Subtract(position));
	if (b <= 0) return IntersectResult::noHit;

	IntersectResult result;
	result.geometry = this;
	result.distance = -b / a;
	result.position = ray.GetPoint(result.distance);
	result.normal = normal;
	return result;
}

}