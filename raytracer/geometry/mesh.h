#ifndef _RAYTRACER_MESH_H_
#define _RAYTRACER_MESH_H_

#include "base/header.h"
#include "base/vector3.h"
#include "base/ray3.h"
#include "geometry.h"

namespace rt
{

struct Mesh : Geometry
{
	Mesh(const std::vector<Vector3>& _vertices, const std::vector<u32>& _indices);

	virtual void Initialize();
	virtual const IntersectResult Intersect(const Ray3& ray) const;

	const IntersectResult IntersectTriangle(const Ray3& ray,
		const Vector3& v0, const Vector3& v1, const Vector3& v2) const;

	const Vector3 TranslateToLocal(const Vector3& v) const;
	bool CheckPoint(float x, float y, float z) const;
	bool CheckPoint(const Vector3& v) const;

	//Vector3 position = Vector3::zero;
	//Vector3 up = Vector3::up;
	//Vector3 right = Vector3::right;
	//Vector3 front = Vector3::front;
	//Vector3 down = Vector3::down;
	//Vector3 left = Vector3::left;
	//Vector3 back = Vector3::back;
	//float length = 1.f;
	//float width = 1.f;
	//float height = 1.f;

	std::vector<Vector3> vertices;
	std::vector<u32> indices;
};


}

#endif //!_RAYTRACER_CUBOID_H_
