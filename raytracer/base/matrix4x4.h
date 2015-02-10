#ifndef _RAYTRACER_MATRIX4X4_H_
#define _RAYTRACER_MATRIX4X4_H_

#include "header.h"
#include "base/vector3.h"
#include "base/quaternion.h"

namespace rt
{
struct Matrix4x4
{
	float m[16];

	Matrix4x4() = default;
	Matrix4x4(float* _m);
	Matrix4x4(const Vector3& p, const Quaternion& q, const Vector3& s);

	float Get(int r, int c);

	void Identity();
	bool IsIdentity();

	const Matrix4x4 Inverse() const;
	const Matrix4x4 Transpose() const;

	const Matrix4x4 Multiply(const Matrix4x4& mat) const;
	const Matrix4x4 operator*(const Matrix4x4& mat) const;

	const Vector3 MultiplyPoint(const Vector3& p) const;
	const Vector3 MultiplyVector(const Vector3& p) const;

	//static const Matrix4x4 Ortho(float left, float right, float bottom, float top, float z_near, float z_far);
	//static const Matrix4x4 Perspective(float fov, float aspect, float z_near, float z_far);

	static const Matrix4x4 identity;

protected:
	void Fill(float val);

	void AssignTranslation(const Vector3& translation);

	void AssignRotation(const Quaternion& quaternion);
	//void AssignRotationX(float radians);
	//void AssignRotationY(float radians);
	//void AssignRotationZ(float radians);

	void AssignScaling(const Vector3& scaling);
};

}

#endif //_RAYTRACER_MATRIX4X4_H_