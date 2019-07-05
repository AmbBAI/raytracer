#ifndef _RAYTRACER_APPLICATION_H_
#define _RAYTRACER_APPLICATION_H_

#include "header.h"
#include "color.h"

namespace rt
{

class Application
{
	Application();

public:
	static Application* GetInstance();
	typedef void(*LoopFunc)();
	bool CreateApplication(const char* title, int width, int height);
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	void RunLoop(LoopFunc loopFunc);

	void Clear(Color32 color);
	void Submit();
	bool SetPixel(int x, int y, const Color32& color);
	bool SetPixel(int x, int y, const Color& color);

private:
    GLFWwindow* window;

	std::vector<u32> pixels;

	int width;
	int height;
};

}

#endif // !_RAYTRACER_APPLICATION_H_
