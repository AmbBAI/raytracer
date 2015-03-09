#include "checker_material.h"
#include "base/mathf.h"

namespace rt
{


CheckerMaterial::CheckerMaterial(float _scale, float _reflectiveness)
	: scale(_scale)
	, Material(_reflectiveness)
{
}

const Color CheckerMaterial::Sample(const Ray3& ray, const Vector3& position, const Vector3& normal) const
{
	float tmp = Mathf::Abs(Mathf::Floor(position.x * 0.1f) + Mathf::Floor(position.z * scale));
	return Mathf::RoundToInt(tmp) & 1 ? Color::white : Color::black;
}

}