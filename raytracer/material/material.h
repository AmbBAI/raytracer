#ifndef _RAYTRACER_MATERIAL_H_
#define _RAYTRACER_MATERIAL_H_

#include "base/header.h"
#include "base/color.h"
#include "base/vector3.h"
#include "base/ray3.h"

namespace rt
{

struct Material
{
	float reflectiveness = 0.5f;

	Material(float _reflectiveness) : reflectiveness(_reflectiveness) {}

	virtual const Color Sample(const Ray3& ray, const Vector3& position, const Vector3& normal) const
	{
		return Color::black;
	}
};

}

#endif // !_RAYTRACER_MATERIAL_H_