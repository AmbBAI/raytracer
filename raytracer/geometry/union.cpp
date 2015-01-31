#include "union.h"
#include "base/mathf.h"

namespace rt
{

Union::Union(Geometry* g1, Geometry* g2)
{
	geometries.push_back(g1);
	geometries.push_back(g2);
}

Union::Union(Geometry* g1, Geometry* g2, Geometry* g3)
{
	geometries.push_back(g1);
	geometries.push_back(g2);
	geometries.push_back(g3);
}

Union::Union(Geometry* g1, Geometry* g2, Geometry* g3, Geometry* g4)
{
	geometries.push_back(g1);
	geometries.push_back(g2);
	geometries.push_back(g3);
	geometries.push_back(g4);
}

//Union::Union(Geometry* g[], int count)
//{
//	geometries.assign(g, g + count)
//}

void Union::Initialize()
{
	for (int i = 0; i < geometries.size(); ++i)
	{
		if (Geometry* g = geometries[i])
		{
			g->Initialize();
		}
	}
}

const IntersectResult Union::Intersect(const Ray3& ray) const
{
	float minDistance = Mathf::inifinity;
	IntersectResult minResult = IntersectResult::noHit;

	for (int i = 0; i < geometries.size(); ++i)
	{
		IntersectResult result;
		if (Geometry* g = geometries[i])
		{
			result = g->Intersect(ray);
		}
		if (result.geometry && result.distance < minDistance)
		{
			minDistance = result.distance;
			minResult = result;
		}
	}
	return minResult;
}

}