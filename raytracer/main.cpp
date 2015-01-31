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

	clock_t start_t = clock();

	rt::Plane plane = rt::Plane(rt::Vector3::up, 0.f);
	rt::CheckerMaterial checker = rt::CheckerMaterial(0.1f, 0.5f);
	plane.material = &checker;

	rt::Sphere redSphere = rt::Sphere(rt::Vector3(-10, 10, -10), 10.f);
	rt::PhongMaterial redPhone = rt::PhongMaterial(rt::Color::red, rt::Color::white, 16.f, 0.25f);
	redSphere.material = &redPhone;

	rt::Sphere blueSphere = rt::Sphere(rt::Vector3(10, 10, -10), 10.f);
	rt::PhongMaterial bluePhone = rt::PhongMaterial(rt::Color::blue, rt::Color::white, 16.f, 0.25f);
	blueSphere.material = &bluePhone;

	rt::Union scene = rt::Union(&plane, &redSphere, &blueSphere);

	rt::PerspectiveCamera camera = rt::PerspectiveCamera(rt::Vector3(0, 5, 15), rt::Vector3::front, rt::Vector3::up, 90);

	RenderRayTraceReflection(canvas, scene, camera, 3);

	clock_t end_t = clock();
	printf("%ld ms\n", end_t - start_t);


	canvas->EndDraw();
}
