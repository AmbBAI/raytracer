#ifndef _RAYTRACER_APPLICATION_H_
#define _RAYTRACER_APPLICATION_H_

#include "header.h"

namespace rt
{

class Canvas;
class Application
{
	Application();

public:
	static Application* GetInstance();
	typedef void(*LoopFunc)();
	bool CreateApplication(int argc, char *argv[], const char* title, int width, int height);

	void SetRunLoop(LoopFunc loopFunc) { this->loopFunc = loopFunc; }
	void RunLoop();

	Canvas* GetCanvas();

private:
	LoopFunc	loopFunc;

    GLFWwindow* window;
    
	int width;
	int height;

	bool isConsoleVisible;
};

}

#endif // !_RAYTRACER_APPLICATION_H_
