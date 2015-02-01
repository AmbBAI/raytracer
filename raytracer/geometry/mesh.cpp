#include "mesh.h"
#include "base/mathf.h"

namespace rt
{

Mesh::Mesh(const std::vector<Vector3>& _vertices, const std::vector<u32>& _indices)
	: vertices(_vertices)
	, indices(_indices)
{

}

void Mesh::Initialize()
{

}

const IntersectResult Mesh::Intersect(const Ray3& ray) const
{
	float minDistance = Mathf::inifinity;
	IntersectResult minResult = IntersectResult::noHit;

	for (int i = 0; i + 2 < indices.size(); i += 3)
	{
		IntersectResult result;
		result = IntersectTriangle(ray,
			vertices[indices[i]],
			vertices[indices[i+1]],
			vertices[indices[i+2]]);

		if (result.geometry && result.distance < minDistance)
		{
			minDistance = result.distance;
			minResult = result;
		}
	}
	return minResult;
}

const IntersectResult Mesh::IntersectTriangle(const Ray3& ray, const Vector3& v0, const Vector3& v1, const Vector3& v2) const
{
	Vector3 edge1 = v1.Subtract(v0);
	Vector3 edge2 = v2.Subtract(v0);
	Vector3 pvec = ray.direction.Cross(edge2);
	double det = edge1.Dot(pvec);

	if (det <= 0) return IntersectResult::noHit;

	Vector3 tvec = ray.origin.Subtract(v0);
	float u = tvec.Dot(pvec);

	if (u < 0 || u > det) return IntersectResult::noHit;

	Vector3 qvec = tvec.Cross(edge1);
	float v = ray.direction.Dot(qvec);
	if (v < 0 || u + v > det) return IntersectResult::noHit;

	float t = edge2.Dot(qvec);
	float inv_det = 1. / det;
	t *= inv_det;
	u *= inv_det;
	v *= inv_det;

	IntersectResult result;
	result.geometry = this;
	result.distance = t;
	result.position = ray.GetPoint(t);
	result.normal = edge1.Cross(edge2).Normalize();
	return result;
}

}