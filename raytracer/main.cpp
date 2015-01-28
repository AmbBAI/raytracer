#include "header.h"
#include "application.h"
#include "canvas.h"
#include "sphere.h"
#include "camera.h"
#include "mathf.h"

rt::Application* app;
rt::Canvas* canvas;
void MainLoop();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	app = rt::Application::GetInstance();
	app->CreateApplication(hInstance, "raytracer", 512, 512);
	canvas = app->GetCanvas();
	app->SetConsoleVisible(true);
	app->SetRunLoop(MainLoop);
	app->RunLoop();
	return 0;
}

void RenderDepth(rt::Canvas* canvas, rt::Sphere& scene, rt::PerspectiveCamera& camera, float maxDepth);
void MainLoop()
{
	canvas->BeginDraw();

	//int w = canvas->GetWidth();
	//int h = canvas->GetHeight();

	//for (int y = 0; y < h; ++y)
	//{
	//	for (int x = 0; x < w; ++x)
	//	{
	//		canvas->SetPixel(x, y,
	//			rt::Color32(255, (int)((float)x / w * 255), (int)((float)y / h * 255), 0));
	//	}
	//}

	RenderDepth(canvas,
		rt::Sphere(rt::Vector3(0, 10, -10), 10),
		rt::PerspectiveCamera(rt::Vector3(0, 10, 10), rt::Vector3::front, rt::Vector3::up, 90),
		20);

	canvas->EndDraw();
}

void RenderDepth(rt::Canvas* canvas, rt::Sphere& scene, rt::PerspectiveCamera& camera, float maxDepth)
{
	scene.Initialize();
	camera.Initialize();

	int w = canvas->GetWidth();
	int h = canvas->GetHeight();

	rt::Ray3 ray = camera.GenerateRay(0.5, 0.5);

	int i = 0;
	for (int y = 0; y < h; ++y)
	{
		float sy = 1.f - (float)y / h;
		for (int x = 0; x < w; ++x)
		{
			float sx = (float)x / w;
			rt::Ray3 ray = camera.GenerateRay(sx, sy);
			rt::IntersectResult result = scene.Intersect(ray);
			if (result.geometry)
			{
				int depth = 255 - (int)rt::Mathf::Min(result.distance / maxDepth * 255, 255);
				canvas->SetPixel(x, y, rt::Color32(255, depth, depth, depth));
			}
		}
	}
}
