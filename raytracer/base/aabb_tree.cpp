#include "aabb_tree.h"
#include "mathf.h"

namespace rt
{


AABBTree::AABBTree()
{

}

AABBTree::AABBTree(const std::vector<Geometry*>& objs, int depth)
{
	assert(depth > 0);

	//nodes.clear();
	//nodes.push_back(AABBNode());
	nodes.assign(1 << depth, AABBNode());
	BuildTree(objs, depth, auto_idx = 0);
}

void AABBTree::BuildTree(const std::vector<Geometry*>& objs, int depth, int idx)
{
	int n = (int)objs.size();
	assert(n > 0);

	if (n == 1 || depth == 1)
	{
		nodes[idx].objs = objs;
		nodes[idx].aabb = objs[0]->aabb;
		for (int i = 1; i < n; ++i)
		{
			nodes[idx].aabb = nodes[idx].aabb.Combine(objs[i]->aabb);
		}
		nodes[idx].left = -1;
		nodes[idx].right = -1;
		return;
	}

	float sumX = 0.f, sumY = 0.f, sumZ = 0.f;
	for (int i = 0; i < n; ++i)
	{
		sumX += objs[i]->aabb.centerX;
		sumY += objs[i]->aabb.centerY;
		sumZ += objs[i]->aabb.centerZ;
	}
	float avgX = sumX / n;
	float avgY = sumY / n;
	float avgZ = sumZ / n;

	float devX = 0.f, devY = 0.f, devZ = 0.f;
	for (int i = 0; i < n; ++i){
		devX += (objs[i]->aabb.centerX - avgX) * (objs[i]->aabb.centerX - avgX);
		devY += (objs[i]->aabb.centerY - avgY) * (objs[i]->aabb.centerY - avgY);
		devZ += (objs[i]->aabb.centerZ - avgZ) * (objs[i]->aabb.centerZ - avgZ);
	}

	std::vector<Geometry*> lObjs;
	std::vector<Geometry*> rObjs;
	if (devX >= Mathf::Max(devY, devZ))
	{
		for (int i = 0; i < n; ++i)
		{
			if (Geometry* geometry = objs[i])
			{
				if (geometry->aabb.centerX < avgX)
				{
					lObjs.push_back(geometry);
				}
				else
				{
					rObjs.push_back(geometry);
				}
			}
		}
	}
	else if (devY >= devX)
	{
		for (int i = 0; i < n; ++i)
		{
			if (Geometry* geometry = objs[i])
			{
				if (geometry->aabb.centerY < avgY)
				{
					lObjs.push_back(geometry);
				}
				else
				{
					rObjs.push_back(geometry);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < n; ++i)
		{
			if (Geometry* geometry = objs[i])
			{
				if (geometry->aabb.centerZ < avgZ)
				{
					lObjs.push_back(geometry);
				}
				else
				{
					rObjs.push_back(geometry);
				}
			}
		}
	}

	if (lObjs.size() <= 0 || rObjs.size() <= 0)
	{
		nodes[idx].objs = objs;
		nodes[idx].aabb = objs[0]->aabb;
		for (int i = 1; i < n; ++i)
		{
			nodes[idx].aabb = nodes[idx].aabb.Combine(objs[i]->aabb);
		}
		nodes[idx].left = -1;
		nodes[idx].right = -1;
		return;
	}

	//nodes.push_back(AABBNode());
	//int left_idx = (int)nodes.size() - 1;
	//nodes.push_back(AABBNode());
	//int right_idx = (int)nodes.size() - 1;
	int left_idx = ++auto_idx;
	BuildTree(lObjs, depth - 1, left_idx);
	int right_idx = ++auto_idx;
	BuildTree(rObjs, depth - 1, right_idx);

	nodes[idx].aabb = nodes[left_idx].aabb.Combine(nodes[right_idx].aabb);
	nodes[idx].left = left_idx;
	nodes[idx].right = right_idx;
}

const IntersectResult AABBTree::Intersect(const Ray3& ray) const
{
	return NodeIntersect(ray, nodes[0]);
}

const IntersectResult AABBTree::NodeIntersect(const Ray3& ray, const AABBNode& node) const
{
	if (!node.aabb.Intersect(ray)) return IntersectResult::noHit;

	float minDistance = Mathf::inifinity;
	IntersectResult minResult = IntersectResult::noHit;

	if (node.left >= 0)
	{
		IntersectResult result = NodeIntersect(ray, nodes[node.left]);

		if (result.geometry && result.distance < minDistance)
		{
			minDistance = result.distance;
			minResult = result;
		}
	}

	if (node.right >= 0)
	{
		IntersectResult result = NodeIntersect(ray, nodes[node.right]);

		if (result.geometry && result.distance < minDistance)
		{
			minDistance = result.distance;
			minResult = result;
		}
	}

	for (int i = 0; i < (int)node.objs.size(); ++i)
	{
		IntersectResult result = node.objs[i]->Intersect(ray);

		if (result.geometry && result.distance < minDistance)
		{
			minDistance = result.distance;
			minResult = result;
		}
	}
	return minResult;
}

}