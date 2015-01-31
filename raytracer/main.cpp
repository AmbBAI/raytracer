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

float pos = 0.f;
void MainLoop()
{
	canvas->BeginDraw();

	pos += 0.1f;

	clock_t start_t = clock();

	rt::Plane plane = rt::Plane(rt::Vector3::up, 0.f);
	rt::CheckerMaterial checker = rt::CheckerMaterial(0.1f, 0.5f);
	plane.material = &checker;

	rt::Sphere redObject = rt::Sphere(rt::Vector3(-10, 10, -10), 10.f);
	rt::PhongMaterial redPhone = rt::PhongMaterial(rt::Color::red, rt::Color::white, 16.f, 0.25f);
	redObject.material = &redPhone;

	rt::Cuboid blueObject = rt::Cuboid(rt::Vector3(10, 10, -10), rt::Vector3::up, rt::Vector3::front, 12.f, 12.f, 20.f);
	rt::PhongMaterial bluePhone = rt::PhongMaterial(rt::Color::blue, rt::Color::white, 16.f, 0.25f);
	blueObject.material = &bluePhone;

	rt::Union scene = rt::Union(&plane, &redObject, &blueObject);

	rt::PerspectiveCamera camera = rt::PerspectiveCamera(rt::Vector3(0, 10, 15), rt::Vector3::front, rt::Vector3::up, 90);

	RenderRayTraceReflection(canvas, scene, camera, 5);

	clock_t end_t = clock();
	printf("%ld ms\n", end_t - start_t);


	canvas->EndDraw();
}
