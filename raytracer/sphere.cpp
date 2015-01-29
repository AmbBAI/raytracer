#include "sphere.h"
#include "mathf.h"

namespace rt
{
const IntersectResult IntersectResult::noHit = IntersectResult();


Sphere::Sphere(const Vector3& _center, float _radius)
	: center(_center), radius(_radius)
{
}

void Sphere::Initialize()
{
	sqrRadius = radius * radius;
}

const IntersectResult Sphere::Intersect(const Ray3& ray) const
{
	Vector3 v = ray.origin.Subtract(center);
	float a0 = v.SqrLength() - sqrRadius;
	float DdotV = ray.direction.Dot(v);

	if (DdotV <= 0)
	{
		float discr = DdotV * DdotV - a0;
		if (discr >= 0)
		{
			IntersectResult result;
			result.geometry = this;
			result.distance = -DdotV - Mathf::Sqrt(discr);
			result.position = ray.GetPoint(result.distance);
			result.normal = result.position.Subtract(center).Normalize();
			return result;
		}
	}
	return IntersectResult::noHit;
}

}