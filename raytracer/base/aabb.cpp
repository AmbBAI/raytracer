#include "aabb.h"
#include "base/mathf.h"

namespace rt
{

AABB::AABB()
{
}


AABB::AABB(float _minX, float _minY, float _minZ,
	float _maxX, float _maxY, float _maxZ)
{
	minX = Mathf::Min(_minX, _maxX);
	maxX = Mathf::Max(_minX, _maxX);
	minY = Mathf::Min(_minY, _maxY);
	maxY = Mathf::Max(_minY, _maxY);
	minZ = Mathf::Min(_minZ, _maxZ);
	maxZ = Mathf::Max(_minZ, _maxZ);

	centerX = (minX + maxX) * 0.5f;
	centerY = (minY + maxY) * 0.5f;
	centerZ = (minZ + maxZ) * 0.5f;
}

AABB::AABB(const Vector3& p)
{
	minX = maxX = centerX = p.x;
	minY = maxY = centerY = p.y;
	minZ = maxZ = centerZ = p.z;
}

AABB::AABB(const Vector3& p1, const Vector3& p2)
	:AABB (p1.x, p1.y, p1.z, p2.x, p2.y, p2.z)
{
}

const AABB AABB::Combine(const Vector3& p) const
{
	return AABB(
		Mathf::Min(minX, p.x),
		Mathf::Min(minY, p.y),
		Mathf::Min(minZ, p.z),
		Mathf::Max(maxX, p.x),
		Mathf::Max(maxY, p.y),
		Mathf::Max(maxZ, p.z)
		);
}

const AABB AABB::Combine(const AABB& aabb) const
{
	return AABB(
		Mathf::Min(minX, aabb.minX),
		Mathf::Min(minY, aabb.minY),
		Mathf::Min(minZ, aabb.minZ),
		Mathf::Max(maxX, aabb.maxX),
		Mathf::Max(maxY, aabb.maxY),
		Mathf::Max(maxZ, aabb.maxZ)
		);
}

bool AABB::Intersect(const Ray3& ray) const
{
	float disNear[3] = { 0 }, disFar[3] = { 0 };

	if (ray.direction.x == 0.f)
	{
		disFar[0] = Mathf::inifinity;
		disNear[0] = -Mathf::inifinity;
	}
	else
	{
		float invX = 1.f / ray.direction.x;

		if (invX > 0.f)
		{
			disNear[0] = (minX - ray.origin.x) * invX;
			disFar[0] = (maxX - ray.origin.x) * invX;
		}
		else
		{
			disNear[0] = (maxX - ray.origin.x) * invX;
			disFar[0] = (minX - ray.origin.x) * invX;
		}
	}

	if (ray.direction.y == 0.f)
	{
		disFar[1] = Mathf::inifinity;
		disNear[1] = -Mathf::inifinity;
	}
	else
	{
		float invY = 1.f / ray.direction.y;

		if (invY > 0.f)
		{
			disNear[1] = (minY - ray.origin.y) * invY;
			disFar[1] = (maxY - ray.origin.y) * invY;
		}
		else
		{
			disNear[1] = (maxY - ray.origin.y) * invY;
			disFar[1] = (minY - ray.origin.y) * invY;
		}
	}

	if (ray.direction.z == 0.f)
	{
		disFar[2] = Mathf::inifinity;
		disNear[2] = -Mathf::inifinity;
	}
	else
	{
		float invZ = 1.f / ray.direction.z;

		if (invZ > 0.f)
		{
			disNear[2] = (minZ - ray.origin.z) * invZ;
			disFar[2] = (maxZ - ray.origin.z) * invZ;
		}
		else
		{
			disNear[2] = (maxZ - ray.origin.z) * invZ;
			disFar[2] = (minZ - ray.origin.z) * invZ;
		}
	}

	float maxNear = Mathf::Max(disNear, 3);
	float minFar = Mathf::Min(disFar, 3);

	if (minFar >= maxNear)
	{
		if (minFar < 0.f) return false;
		return true;
	}
	return false;
}

}