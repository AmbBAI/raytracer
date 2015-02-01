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

const rt::Polygon CreateMesh();
void MainLoop()
{
	canvas->BeginDraw();

	clock_t start_t = clock();

	//rt::Plane plane = rt::Plane(rt::Vector3::up, 0.f);
	//rt::CheckerMaterial checker = rt::CheckerMaterial(0.1f, 0.5f);
	//plane.material = &checker;

	rt::PhongMaterial greenPhone = rt::PhongMaterial(rt::Color::green, rt::Color::white, 16.f, 0.25f);
	rt::Polygon teaportTop = rt::Polygon("resources/teapot/teapot.obj", 1);
	teaportTop.material = &greenPhone;
	rt::Polygon teaportBase = rt::Polygon("resources/teapot/teapot.obj", 0);
	teaportBase.material = &greenPhone;

	//rt::Sphere redObject = rt::Sphere(rt::Vector3(-10, 10, -10), 10.f);
	//rt::PhongMaterial redPhone = rt::PhongMaterial(rt::Color::red, rt::Color::white, 16.f, 0.25f);
	//redObject.material = &redPhone;

	//rt::Cuboid blueObject = rt::Cuboid(rt::Vector3(10, 10, -10), rt::Vector3(0 , 1, 0.5).Normalize(), rt::Vector3(1, -0.5, 0).Normalize(), 12.f, 12.f, 12.f);
	//rt::PhongMaterial bluePhone = rt::PhongMaterial(rt::Color::blue, rt::Color::white, 16.f, 0.25f);
	//blueObject.material = &bluePhone;

	rt::Union scene = rt::Union(&teaportTop, &teaportBase);

	rt::PerspectiveCamera camera = rt::PerspectiveCamera(rt::Vector3(0, 50, 100), rt::Vector3::front, rt::Vector3::up, 90);

	RenderNormal(canvas, scene, camera);

	clock_t end_t = clock();
	printf("%ld ms\n", end_t - start_t);

	canvas->EndDraw();
}

const rt::Polygon CreateMesh()
{
	std::vector<rt::Vector3> vertices;
	std::vector<u32> indices;

	vertices.push_back(rt::Vector3(2, 8, 5));
	vertices.push_back(rt::Vector3(2, 15, 0));
	vertices.push_back(rt::Vector3(-3, 5, 0));
	vertices.push_back(rt::Vector3(8, 5, 0));

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(1);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(2);

	return rt::Polygon(vertices, indices);
}
