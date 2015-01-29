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

	bool CreateApplication(HINSTANCE hInstance, const char* title, int width, int height);
	void SetRunLoop(LoopFunc loopFunc) { this->loopFunc = loopFunc; }
	void RunLoop() { MainLoop(); }

	void SetConsoleVisible(bool isVisible);

	Canvas* GetCanvas();

protected:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT	MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bUseDefWindowsProc);
	BOOL	PreTranslateMessage(MSG* uMsg) { return TRUE; }
	LRESULT	MainLoop();

private:
	HWND		hAppWindow;
	HINSTANCE	hAppInstance;
	LoopFunc	loopFunc;

	int width;
	int height;

	bool isConsoleVisible;
};

}

#endif // !_RAYTRACER_APPLICATION_H_
