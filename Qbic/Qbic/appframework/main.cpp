#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#include <windows.h>
#include <windowsx.h>
#include <string>
#include "util.h"

#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif // _UNICODE

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class App
{
private:
	std::tstring m_wndClassName;
	std::tstring m_wndTitle;
	HWND m_hwnd;
	MSG m_msg;
	WNDCLASS m_wndClass;
	size_t m_wndWidth;
	size_t m_wndHeight;

	static App m_instance;

	App() {}
	~App() {}

public:

	std::tstring GetWndTitle() { return m_wndTitle; }
	HWND GetWndHandle() { return m_hwnd; }
	size_t GetWndWidth() { return m_wndWidth; }
	size_t GetWndHeight() { return m_wndHeight; }

	static App* GetInstance() {
		return &m_instance;
	}

	bool InitWindow(std::tstring &title, std::tstring &wndclassname, HINSTANCE &hinstance, WNDPROC wndproc, size_t width, size_t height)
	{
		m_wndTitle = title;
		m_wndClassName = wndclassname;
		m_wndWidth = width;
		m_wndHeight = height;

		m_wndClass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		m_wndClass.lpfnWndProc = wndproc;
		m_wndClass.cbClsExtra = 0;
		m_wndClass.cbWndExtra = 0;
		m_wndClass.hInstance = hinstance;
		m_wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		m_wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		m_wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		m_wndClass.lpszMenuName = NULL;
		m_wndClass.lpszClassName = m_wndClassName.c_str();

		if (!RegisterClass(&m_wndClass))
		{
			MessageBox(NULL, TEXT("Program requires Windows NT!"), m_wndClassName.c_str(), MB_ICONERROR);
			return false;
		}

		m_hwnd = CreateWindow(m_wndClassName.c_str(), m_wndTitle.c_str(),
			WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION,
			CW_USEDEFAULT, CW_USEDEFAULT,
			width, height,
			NULL, NULL, hinstance, NULL);
		if (!m_hwnd)
		{
			MessageBox(NULL, TEXT("Failed to Create Window!"), m_wndClassName.c_str(), MB_ICONERROR);
			return false;
		}

		RECT window_rect = { 0, 0, width - 1, height - 1 };
		AdjustWindowRectEx(&window_rect, GetWindowStyle(m_hwnd), GetMenu(m_hwnd) != NULL, GetWindowExStyle(m_hwnd));
		MoveWindow(m_hwnd, 0, 0, window_rect.right - window_rect.left, window_rect.bottom - window_rect.top, FALSE);

		ShowWindow(m_hwnd, SW_SHOW);
		UpdateWindow(m_hwnd);

		return GameInit();
	}

	WPARAM Run()
	{
		while (true)
		{
			if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
			{
				if (m_msg.message == WM_QUIT)
				{
					break;
				}
				TranslateMessage(&m_msg);
				DispatchMessage(&m_msg);
			}
			GameMain();
		}
		GameShutdown();
		return m_msg.wParam;
	}

	virtual bool GameInit() {
		return true;
	}
	virtual void GameMain() {
		Start_Clock();
		Wait_Clock(30);
	}
	virtual void GameShutdown() {

	}
};

App *gApp = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	gApp = App::GetInstance();
	if (gApp->InitWindow(std::tstring(TEXT("Qbic")), std::tstring(TEXT("Qbic")), hInstance, WndProc, 1024, 768))
	{
		gApp->Run();
	}
	gApp = NULL;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC				hdc;
	PAINTSTRUCT		ps;

	switch (message)
	{
	case WM_CREATE:
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}
