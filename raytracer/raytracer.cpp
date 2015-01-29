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

void RenderDepth(Canvas* canvas, Object& scene, Camera& camera, float maxDepth)
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

void RenderNormal(Canvas* canvas, Object& scene, Camera& camera)
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
