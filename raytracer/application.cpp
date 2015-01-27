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

	WNDCLASS wnd_class;
	ZeroMemory(&wnd_class, sizeof(wnd_class));
	wnd_class.lpszClassName = "App Window";
	wnd_class.lpfnWndProc = (WNDPROC)Application::WndProc;
	wnd_class.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
	wnd_class.hInstance = hInstance;
	wnd_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wnd_class.lpszMenuName = NULL;
	wnd_class.cbClsExtra = 0;
	wnd_class.cbWndExtra = 0;

	BOOL ret = TRUE;

	ret = RegisterClass(&wnd_class);
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
	int work_area_width = workAreaRect.right - workAreaRect.left;
	int work_area_height = workAreaRect.bottom - workAreaRect.top;

	int posX = (work_area_width - wndWidth) / 2;
	int posY = (work_area_height - wndHeight) / 2;

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
		BOOL use_def_win_proc = TRUE;
		LRESULT ge_win_proc_ret = 0;
		ge_win_proc_ret = ptrApp->MsgProc(uMsg, wParam, lParam, use_def_win_proc);
		if (!use_def_win_proc) return ge_win_proc_ret;
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
	HACCEL h_accel = LoadAccelerators(NULL, MAKEINTRESOURCE(0));

	while (WM_QUIT != msg.message)
	{
		BOOL has_msg = PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE);

		if (has_msg)
		{
			if (0 == TranslateAccelerator(hAppWindow, h_accel, &msg))
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