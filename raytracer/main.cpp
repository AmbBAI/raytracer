#include "raytracer.h"

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

void MainLoop()
{
	canvas->BeginDraw();

	rt::CheckerMaterial material = rt::CheckerMaterial(0.6f, 1.f);
	rt::Sphere sphere = rt::Sphere(rt::Vector3(2, 0, -10), 10);
	sphere.material = &material;
	rt::PerspectiveCamera camera = rt::PerspectiveCamera(rt::Vector3(0, 0, 10), rt::Vector3::front, rt::Vector3::up, 90);

	RenderMaterial(canvas, sphere, camera);

	canvas->EndDraw();
}
