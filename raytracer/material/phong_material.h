#ifndef _RAYTRACER_PHONG_MATERIAL_H_
#define _RAYTRACER_PHONG_MATERIAL_H_

#include "material.h"

namespace rt
{

struct PhongMaterial : Material
{
	PhongMaterial(const Color& _diffuse, const Color& _specular, float _shininess, float _reflectiveness);

	virtual const Color Sample(const Ray3& ray, const Vector3& position, const Vector3& normal) const;

	Color diffuse = Color::white;
	Color specular = Color::white;
	float shininess = 1.f;
	//float reflectiveness = 0.f;

	static Vector3 lightDir;
	static Color lightColor;
};

}

#endif // !_RAYTRACER_PHONG_MATERIAL_H_