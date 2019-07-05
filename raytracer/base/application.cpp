#include "application.h"

namespace rt
{

Application::Application()
	: width(0)
	, height(0)
{

}

Application* Application::GetInstance()
{
	static Application _GlobalApplication;
	return &_GlobalApplication;
}

bool Application::CreateApplication(const char* title, int width, int height)
{
	assert(width > 0);
	assert(height > 0);

    if (!glfwInit()) return false;

	glfwWindowHint(GLFW_DOUBLEBUFFER, 0);
	glfwWindowHint(GLFW_RESIZABLE, 0);
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) return false;
    
    glfwMakeContextCurrent(window);
	
    this->width = width;
	this->height = height;

	pixels.assign(width * height, Color32::black.rgba);
	return true;
}

void Application::RunLoop(LoopFunc loopFunc)
{
    assert(window != nullptr);
	while (!glfwWindowShouldClose(window))
    {
        if (loopFunc != nullptr) loopFunc();
		glfwPollEvents();
    }
    glfwTerminate();
}

void Application::Clear(Color32 color)
{
	pixels.assign(width * height, color.rgba);
}

void Application::Submit()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
	glFlush();
}

bool Application::SetPixel(int x, int y, const Color32& color)
{
	if (x < 0 || x >= width) return false;
	if (y < 0 || y >= height) return false;

	pixels[(height - y - 1) * width + x] = color.rgba;
	return true;
}

bool Application::SetPixel(int x, int y, const Color& color)
{
	return SetPixel(x, y, Color32(color));
}


}
