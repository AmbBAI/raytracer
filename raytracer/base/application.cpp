#include "application.h"
#include "canvas.h"

namespace rt
{

Application::Application()
	: hAppInstance(NULL)
	, hAppWindow(NULL)
	, loopFunc(NULL)
	, width(0)
	, height(0)
	, isConsoleVisible(false)
{

}

Application* Application::GetInstance()
{
	static Application _GlobalApplication;
	return &_GlobalApplication;
}

bool Application::CreateApplication(HINSTANCE hInstance, const char* title, int width, int height)
{
	this->hAppInstance = hInstance;

	WNDCLASS wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.lpszClassName = "App Window";
	wndClass.lpfnWndProc = (WNDPROC)Application::WndProc;
	wndClass.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = NULL;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;

	BOOL ret = TRUE;

	ret = RegisterClass(&wndClass);
	if (!ret) return false;

	RECT wndRect;
	wndRect.top = 0;
	wndRect.left = 0;
	wndRect.bottom = height;
	wndRect.right = width;

	DWORD wndType = ((WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX) | WS_CLIPCHILDREN | WS_VISIBLE);

	ret = AdjustWindowRect(&wndRect, wndType, FALSE);
	if (!ret) return false;

	RECT workAreaRect;
	if (!SystemParametersInfo(SPI_GETWORKAREA, 0, &workAreaRect, 0))
		return false;

	int wndWidth = wndRect.right - wndRect.left;
	int wndHeight = wndRect.bottom - wndRect.top;
	int workAreaWidth = workAreaRect.right - workAreaRect.left;
	int workAreaHeight = workAreaRect.bottom - workAreaRect.top;

	int posX = (workAreaWidth - wndWidth) / 2;
	int posY = (workAreaHeight - wndHeight) / 2;

	this->hAppWindow = CreateWindow("App Window", title, wndType,
		posX,
		posY,
		wndWidth,
		wndHeight,
		0L, 0L, this->hAppInstance, 0L);
	if (hAppWindow == NULL) return false;

	RECT rect;
	GetClientRect(hAppWindow, &rect);
	this->width = rect.right - rect.left;
	this->height = rect.bottom - rect.top;

	UpdateWindow(hAppWindow);
	ShowWindow(hAppWindow, SW_NORMAL);
	return true;
}

LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Application* ptrApp = Application::GetInstance();
	if (ptrApp)
	{
		BOOL useDefWinProc = TRUE;
		LRESULT winProcResult = 0;
		winProcResult = ptrApp->MsgProc(uMsg, wParam, lParam, useDefWinProc);
		if (!useDefWinProc) return winProcResult;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT Application::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bUseDefWindowsProc)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return 0;
}

LRESULT Application::MainLoop()
{
	MSG  msg;
	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);
	HACCEL hAccel = LoadAccelerators(NULL, MAKEINTRESOURCE(0));

	while (WM_QUIT != msg.message)
	{
		BOOL hasMsg = PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE);

		if (hasMsg)
		{
			if (0 == TranslateAccelerator(hAppWindow, hAccel, &msg))
			{
				if (PreTranslateMessage(&msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
		else
		{
			if (loopFunc != NULL) loopFunc();
		}
	}
	return 0;
}

Canvas* Application::GetCanvas()
{
	if (hAppWindow == NULL) return NULL;

	Canvas* canvas = new Canvas(hAppWindow, width, height);
	return canvas;
}

void Application::SetConsoleVisible(bool isVisible)
{
	if (isConsoleVisible == isVisible) return;

	if (isVisible)
	{
		::FreeConsole();
		if (::AllocConsole())
		{
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);
			isConsoleVisible = isVisible;
		}
	}
	else
	{
		if (::FreeConsole())
		{
			isConsoleVisible = isVisible;
		}
	}
}

}