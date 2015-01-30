#include "phong_material.h"
#include "base/mathf.h"

namespace rt
{

Vector3 PhongMaterial::lightDir = Vector3(1.f, 1.f, 1.f).Normalize();
Color PhongMaterial::lightColor = Color::white;

PhongMaterial::PhongMaterial(const Color& _diffuse, const Color& _specular, float _shininess, float _reflectiveness)
	: diffuse(_diffuse)
	, specular(_specular)
	, shininess(_shininess)
	, reflectiveness(_reflectiveness)
{
}

const Color PhongMaterial::Sample(const Ray3& ray, const Vector3& position, const Vector3& normal) const
{
	float NdotL = normal.Dot(lightDir);
	Vector3 H = (lightDir.Subtract(ray.direction)).Normalize();
	float NdotH = normal.Dot(H);
	Color diffuseTerm = diffuse.Multiply(Mathf::Max(NdotL, 0));
	Color specularTerm = specular.Multiply(Mathf::Pow(Mathf::Max(NdotH, 0), shininess));
	return lightColor.Modulate(diffuseTerm.Add(specularTerm));
}

}