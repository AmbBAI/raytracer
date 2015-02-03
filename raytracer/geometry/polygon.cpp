#include "polygon.h"
#include "base/mathf.h"

#include "thirdpart/tinyobjloader/tiny_obj_loader.h"

namespace rt
{

Polygon::Polygon(const std::vector<Triangle>& _triangles)
	: triangles(_triangles)
{
	triangles_ptr.assign(triangles.size(), nullptr);
	for (int i = 0; i < triangles.size(); ++i)
	{
		triangles_ptr[i] = &triangles[i];
	}
}

Polygon::Polygon(const char* objFile)
{
	std::vector<tinyobj::shape_t> shape;
	std::vector<tinyobj::material_t> material;
	std::string ret = tinyobj::LoadObj(shape, material, objFile);
	
	if (ret.length() != 0)
	{
		printf("%s\n", ret.c_str());
		return;
	}

	triangles.clear();
	for (int s = 0; s < shape.size(); ++s)
	{
		tinyobj::mesh_t& mesh = shape[s].mesh;
		std::vector<float>& positions = mesh.positions;
		std::vector<float>& normals = mesh.normals;
		std::vector<u32>& indices = mesh.indices;

		for (int i = 0; i + 2 < indices.size(); i+=3)
		{
			int a = indices[i] * 3;
			int b = indices[i + 1] * 3;
			int c = indices[i + 2] * 3;

			Triangle triangle = Triangle(
				Vector3(positions[a], positions[a + 1], positions[a + 2]),
				Vector3(positions[b], positions[b + 1], positions[b + 2]),
				Vector3(positions[c], positions[c + 1], positions[c + 2]));

			if (normals.size() > 0)
			{
				triangle.n0 = Vector3(normals[a], normals[a + 1], normals[a + 2]);
				triangle.n1 = Vector3(normals[b], normals[b + 1], normals[b + 2]);
				triangle.n2 = Vector3(normals[c], normals[c + 1], normals[c + 2]);
			}

			triangles.push_back(triangle);

		}
	}

	triangles_ptr.assign(triangles.size(), nullptr);
	for (int i = 0; i < triangles.size(); ++i)
	{
		triangles_ptr[i] = &triangles[i];
	}
}

void Polygon::Initialize()
{

}

const IntersectResult Polygon::Intersect(const Ray3& ray) const
{
	float minDistance = Mathf::inifinity;
	IntersectResult minResult = IntersectResult::noHit;

	for (int i = 0; i < triangles.size(); ++i)
	{
		IntersectResult result = triangles[i].Intersect(ray);

		if (result.geometry && result.distance < minDistance)
		{
			minDistance = result.distance;
			minResult = result;
		}
	}
	return minResult;
}
}