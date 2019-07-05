#include "base/header.h"
#include "base/application.h"
#include "base/color.h"

rt::Application* app;

void MainLoop();

int main(int argc, char *argv[])
{
	app = rt::Application::GetInstance();
	app->CreateApplication("hello", 512, 512);
	app->RunLoop(MainLoop);
	return 0;
}

void MainLoop()
{
	app->Clear(rt::Color32::black);
	
	int w = app->GetWidth();
	int h = app->GetHeight();

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			app->SetPixel(x, y,
				rt::Color(1.f, (float)x / w, (float)y / h, 0.f));
		}
	}

	app->Submit();

}

