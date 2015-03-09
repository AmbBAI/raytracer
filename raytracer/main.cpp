#include "raytracer.h"

rt::Application* app;
rt::Canvas* canvas;
bool drawFinished = false;

void MainLoop();

int main(int argc, char *argv[])
{
	app = rt::Application::GetInstance();
	app->CreateApplication(argc, argv, "raytracer", 512, 512);
	canvas = app->GetCanvas();
	//app->SetConsoleVisible(true);
	app->SetRunLoop(MainLoop);
	app->RunLoop();
	return 0;
}

bool isFinished = false;
void MainLoop()
{
	if (isFinished) return;
	isFinished = true;

	clock_t start_t = clock();

	//rt::Plane plane = rt::Plane(rt::Vector3::up, 0.f);
	rt::CheckerMaterial checker = rt::CheckerMaterial(0.1f, 0.5f);
	//plane.material = &checker;

	//rt::PhongMaterial greenPhone = rt::PhongMaterial(rt::Color::green, rt::Color::white, 16.f, 0.25f);
	rt::Polygon teapot = rt::Polygon("resources/teapot/teapot.obj");
	teapot.SetTransform(rt::Vector3(50.f, 0.f, 0.f), rt::Vector3(0.f, 0.f, 0.f), rt::Vector3(0.5f, 0.5f, 0.5f));
	//teapot.material = &greenPhone;

	//rt::Polygon dragon = rt::Polygon("resources/dragon/dragon.obj");
	//dragon.SetTransform(rt::Vector3(-50.f, 0.f, 0.f), rt::Vector3(0.f, 90.f, 0.f), rt::Vector3(80.f, 80.f, 80.f));

	//rt::Sphere redObject = rt::Sphere(rt::Vector3(-10, 10, -10), 10.f);
	//rt::PhongMaterial redPhone = rt::PhongMaterial(rt::Color::red, rt::Color::white, 16.f, 0.25f);
	//redObject.material = &redPhone;

	//rt::Cuboid blueObject = rt::Cuboid(rt::Vector3(10, 10, -10), rt::Vector3(0 , 1, 0.5).Normalize(), rt::Vector3(1, -0.5, 0).Normalize(), 12.f, 12.f, 12.f);
	//rt::PhongMaterial bluePhone = rt::PhongMaterial(rt::Color::blue, rt::Color::white, 16.f, 0.25f);
	//blueObject.material = &bluePhone;

	//rt::Union scene = rt::Union(&teapot, &dragon);

	rt::PerspectiveCamera camera = rt::PerspectiveCamera(rt::Vector3(0, 50, 100), rt::Vector3::front, rt::Vector3::up, 90);


	canvas->BeginDraw();

	//TestColor(canvas);
	RenderNormal(canvas, teapot, camera);

	canvas->EndDraw();

	clock_t end_t = clock();
	printf("%ld ms\n", end_t - start_t);

}

