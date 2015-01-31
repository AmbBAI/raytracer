#include "cuboid.h"
#include "base/mathf.h"

namespace rt
{
Cuboid::Cuboid(const Vector3& _position, const Vector3& _up, const Vector3& _front, float _length, float _width, float _height)
	: position(_position)
	, up(_up)
	, front(_front)
	, length(_length)
	, width(_width)
	, height(_height)
{
}

void Cuboid::Initialize()
{
	front = front.Normalize();
	up = up.Normalize();
	right = front.Cross(up);
	left = up.Cross(front);
	up = right.Cross(front);
	down = front.Cross(right);
	back = right.Cross(up);

	halfWidth = Mathf::Abs(width / 2.f);
	halfLength = Mathf::Abs(length / 2.f);
	halfHeight = Mathf::Abs(height / 2.f);
}

const IntersectResult Cuboid::Intersect(const Ray3& ray) const
{
	Ray3 tmpRay = ray;

	tmpRay.origin = tmpRay.origin.Subtract(position);
	tmpRay.origin = TranslateToLocal(tmpRay.origin);

	if (CheckPoint(tmpRay.origin))
	{
		return IntersectResult::noHit;
	}

	tmpRay.direction = TranslateToLocal(tmpRay.direction).Normalize();

	float distance = -1.f;

	if (tmpRay.direction.z > 0 && tmpRay.origin.z + halfLength < 0)
		distance = -(tmpRay.origin.z + halfLength) / tmpRay.direction.z;
	else if (tmpRay.direction.z < 0 && tmpRay.origin.z - halfLength > 0)
		distance = -(tmpRay.origin.z - halfLength) / tmpRay.direction.z;
	else distance = -1.0f;

	if (distance > 0)
	{
		Vector3 p = tmpRay.GetPoint(distance);

		if (CheckPoint(p.x, p.y, 0))
		{
			IntersectResult result;
			result.geometry = this;
			result.distance = distance;
			result.position = ray.GetPoint(distance);
			result.normal = p.z > 0 ? front : back;
			return result;
		}
	}

	if (tmpRay.direction.x > 0 && tmpRay.origin.x + halfWidth < 0)
		distance = -(tmpRay.origin.x + halfWidth) / tmpRay.direction.x;
	else if (tmpRay.direction.x < 0 && tmpRay.origin.x - halfWidth > 0)
		distance = -(tmpRay.origin.x - halfWidth) / tmpRay.direction.x;
	else distance = -1.0f;

	if (distance > 0)
	{
		Vector3 p = tmpRay.GetPoint(distance);

		if (CheckPoint(0, p.y, p.z))
		{
			IntersectResult result;
			result.geometry = this;
			result.distance = distance;
			result.position = ray.GetPoint(distance);
			result.normal = p.x > 0 ? right : left;
			return result;
		}
	}

	if (tmpRay.direction.y > 0 && tmpRay.origin.y + halfHeight < 0)
		distance = -(tmpRay.origin.y + halfHeight) / tmpRay.direction.y;
	else if (tmpRay.direction.y < 0 && tmpRay.origin.y - halfHeight > 0)
		distance = -(tmpRay.origin.y - halfHeight) / tmpRay.direction.y;
	else distance = -1.0f;

	if (distance > 0)
	{
		Vector3 p = tmpRay.GetPoint(distance);

		if (CheckPoint(p.x, 0, p.z))
		{
			IntersectResult result;
			result.geometry = this;
			result.distance = distance;
			result.position = ray.GetPoint(distance);
			result.normal = p.y > 0 ? up : down;
			return result;
		}
	}

	return IntersectResult::noHit;
}

const Vector3 Cuboid::TranslateToLocal(const Vector3& v) const
{
	return Vector3(
		v.x * right.x + v.y * up.x + v.z * front.x,
		v.x * right.y + v.y * up.y + v.z * front.y,
		v.x * right.z + v.y * up.z + v.z * front.z);
}

bool Cuboid::CheckPoint(float x, float y, float z) const
{
	if ((x <= halfWidth && x >= -halfWidth)
		&& (y <= halfHeight && y >= -halfHeight)
		&& (z <= halfLength && z >= -halfLength))
	{
		return true;
	}
	return false;
}

bool Cuboid::CheckPoint(const Vector3& v) const
{
	return CheckPoint(v.x, v.y, v.z);
}



}