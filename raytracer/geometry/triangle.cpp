#include "triangle.h"
#include "base/mathf.h"

namespace rt
{

Triangle::Triangle(const Vector3& _v0, const Vector3& _v1, const Vector3& _v2)
	: v0(_v0)
	, v1(_v1)
	, v2(_v2)
{
	e1 = v1.Subtract(v0);
	e2 = v2.Subtract(v0);
	n0 = n1 = n2 = e1.Cross(e2).Normalize();
}

Triangle::Triangle(const Vector3& _v0, const Vector3& _v1, const Vector3& _v2, const Vector3& _n0, const Vector3& _n1, const Vector3& _n2)
	: v0(_v0)
	, v1(_v1)
	, v2(_v2)
	, n0(_n0)
	, n1(_n1)
	, n2(_n2)
{
	e1 = v1.Subtract(v0);
	e2 = v2.Subtract(v0);
}

void Triangle::Initialize()
{
}

const IntersectResult Triangle::Intersect(const Ray3& ray) const
{
	Vector3 pvec = ray.direction.Cross(e2);
	double det = e1.Dot(pvec);

	if (det <= 0) return IntersectResult::noHit;

	Vector3 tvec = ray.origin.Subtract(v0);
	float u = tvec.Dot(pvec);

	if (u < 0 || u > det) return IntersectResult::noHit;

	Vector3 qvec = tvec.Cross(e1);
	float v = ray.direction.Dot(qvec);
	if (v < 0 || u + v > det) return IntersectResult::noHit;

	float t = e2.Dot(qvec);
	float inv_det = 1. / det;
	t *= inv_det;
	u *= inv_det;
	v *= inv_det;

	IntersectResult result;
	result.geometry = this;
	result.distance = t;
	result.position = ray.GetPoint(t);
	result.normal = n0.Multiply(1 - u - v).Add(n1.Multiply(u)).Add(n2.Multiply(v));
	return result;
}

}