#ifndef _RAYTRACER_CHECKER_MATERIAL_H_
#define _RAYTRACER_CHECKER_MATERIAL_H_

#include "material.h"

namespace rt
{

struct CheckerMaterial : Material
{
	CheckerMaterial(float _scale, float _reflectiveness);

	virtual const Color Sample(const Ray3& ray, const Vector3& position, const Vector3& normal) const;

	float scale = 0.5f;
	//float reflectiveness;
};

}

#endif // !_RAYTRACER_CHECKER_MATERIAL_H_