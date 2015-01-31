#include "raytracer.h"
using namespace rt;


void TestColor(Canvas* canvas)
{
	int w = canvas->GetWidth();
	int h = canvas->GetHeight();

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			canvas->SetPixel(x, y,
				Color32(255, (int)((float)x / w * 255), (int)((float)y / h * 255), 0));
		}
	}
}

void RenderDepth(Canvas* canvas, Geometry& scene, Camera& camera, float maxDepth)
{
	scene.Initialize();
	camera.Initialize();

	int w = canvas->GetWidth();
	int h = canvas->GetHeight();

	//rt::Ray3 ray = camera.GenerateRay(0.5, 0.5);

	int i = 0;
	for (int y = 0; y < h; ++y)
	{
		float sy = 1.f - (float)y / h;
		for (int x = 0; x < w; ++x)
		{
			float sx = (float)x / w;
			Ray3 ray = camera.GenerateRay(sx, sy);
			IntersectResult result = scene.Intersect(ray);
			if (result.geometry)
			{
				int depth = 255 - (int)Mathf::Min(result.distance / maxDepth * 255, 255);
				canvas->SetPixel(x, y, Color32(255, depth, depth, depth));
			}
		}
	}
}

void RenderNormal(Canvas* canvas, Geometry& scene, Camera& camera)
{
	scene.Initialize();
	camera.Initialize();

	int w = canvas->GetWidth();
	int h = canvas->GetHeight();

	//rt::Ray3 ray = camera.GenerateRay(0.25, 0.5);
	//rt::IntersectResult result = scene.Intersect(ray);

	int i = 0;
	for (int y = 0; y < h; ++y)
	{
		float sy = 1.f - (float)y / h;
		for (int x = 0; x < w; ++x)
		{
			float sx = (float)x / w;
			Ray3 ray = camera.GenerateRay(sx, sy);
			IntersectResult result = scene.Intersect(ray);
			if (result.geometry)
			{
				Color32 color = Color32::black;
				color.r = u8((result.normal.x + 1.f) * 128);
				color.g = u8((result.normal.y + 1.f) * 128);
				color.b = u8((result.normal.z + 1.f) * 128);
				canvas->SetPixel(x, y, color);
			}
		}
	}
}

void RenderMaterial(rt::Canvas* canvas, rt::Geometry& scene, rt::Camera& camera)
{
	scene.Initialize();
	camera.Initialize();

	int w = canvas->GetWidth();
	int h = canvas->GetHeight();

	//rt::Ray3 ray = camera.GenerateRay(0.25, 0.5);
	//rt::IntersectResult result = scene.Intersect(ray);

	int i = 0;
	for (int y = 0; y < h; ++y)
	{
		float sy = 1.f - (float)y / h;
		for (int x = 0; x < w; ++x)
		{
			float sx = (float)x / w;
			Ray3 ray = camera.GenerateRay(sx, sy);
			IntersectResult result = scene.Intersect(ray);
			if (result.geometry)
			{
				Color color = Color::black;
				if (Material* material = result.geometry->material)
				{
					color = material->Sample(ray, result.position, result.normal);
				}
				canvas->SetPixel(x, y, color);
			}
		}
	}
}

const Color RayTraceRecursive(rt::Geometry& scene, const Ray3& ray, int maxReflect)
{
	IntersectResult result = scene.Intersect(ray);

	if (result.geometry && result.geometry->material)
	{
		float reflectiveness = result.geometry->material->reflectiveness;
		Color color = result.geometry->material->Sample(ray, result.position, result.normal);
		color = color.Multiply(1.f - reflectiveness);

		if (reflectiveness > 0.f && maxReflect > 0)
		{
			Vector3 r = result.normal.Multiply(-2 * result.normal.Dot(ray.direction)).Add(ray.direction);
			Ray3 reflectedRay = Ray3(result.position, r);
			Color reflectedColor = RayTraceRecursive(scene, reflectedRay, maxReflect - 1);
			color = color.Add(reflectedColor.Multiply(reflectiveness));
		}
		return color;
	}
	return Color::black;
}

void RenderRayTraceReflection(rt::Canvas* canvas, rt::Geometry& scene, rt::Camera& camera, int maxReflect)
{
	scene.Initialize();
	camera.Initialize();

	int w = canvas->GetWidth();
	int h = canvas->GetHeight();

	//rt::Ray3 ray = camera.GenerateRay(0.25, 0.5);
	//rt::IntersectResult result = scene.Intersect(ray);

	int i = 0;
	for (int y = 0; y < h; ++y)
	{
		float sy = 1.f - (float)y / h;
		for (int x = 0; x < w; ++x)
		{
			float sx = (float)x / w;
			Ray3 ray = camera.GenerateRay(sx, sy);
			Color color = RayTraceRecursive(scene, ray, maxReflect);
			canvas->SetPixel(x, y, color);
		}
	}
}