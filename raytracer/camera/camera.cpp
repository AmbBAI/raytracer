#include "camera.h"
#include "base/mathf.h"

namespace rt
{


PerspectiveCamera::PerspectiveCamera(const Vector3& _eye, const Vector3& _front, const Vector3& _up, float _fov)
	: eye(_eye)
	, front(_front)
	, refUp(_up)
	, fov(_fov)
{
}

void PerspectiveCamera::Initialize()
{
	right = front.Cross(refUp);
	up = right.Cross(front);
	fovScale = Mathf::Tan(fov * 0.5f * Mathf::deg2rad) * 2.f;
}

const Ray3 PerspectiveCamera::GenerateRay(float x, float y) const
{
	Vector3 r = right.Multiply((x - 0.5f) * fovScale);
	Vector3 u = up.Multiply((y - 0.5f) * fovScale);
	return Ray3(eye, front.Add(r).Add(u).Normalize());
}

}