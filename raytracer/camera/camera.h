#ifndef _RAYTRACER_CAMERA_H_
#define _RAYTRACER_CAMERA_H_

#include "base/header.h"
#include "base/vector3.h"
#include "base/ray3.h"

namespace rt
{

struct Camera
{
	virtual void Initialize() = 0;
	virtual const Ray3 GenerateRay(float x, float y) const = 0;
};

struct PerspectiveCamera : Camera
{
	PerspectiveCamera(
		const Vector3& _eye,
		const Vector3& _front,
		const Vector3& _up,
		float _fov
		);

	virtual void Initialize();
	virtual const Ray3 GenerateRay(float x, float y) const;

private:
	Vector3 eye = Vector3::zero;
	Vector3 front = Vector3::front;
	Vector3 up = Vector3::up;
	float fov = 90.f;

	Vector3 right = Vector3::zero;
	Vector3 refUp = Vector3::up;
	float fovScale = 0.f;
};

}

#endif //!_RAYTRACER_CAMERA_H_