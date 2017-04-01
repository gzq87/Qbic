#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#include <windows.h>
#include <windowsx.h>
#include <string>
#include <ctime>
#include "util.h"

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

	//HDC m_hDC;
	HDC m_hCompatibleDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	

	UINT32 *m_framebuffer;
	float *m_zbuffer;

	static App *m_instance;

	App():m_wndWidth(0), m_wndHeight(0), m_framebuffer(NULL), m_zbuffer(NULL), m_hCompatibleDC(NULL), m_hBitmap(NULL), m_hOldBitmap(NULL) {}
	

public:
	virtual ~App() {}

	std::tstring GetWndTitle() { return m_wndTitle; }
	HWND GetWndHandle() { return m_hwnd; }
	size_t GetWndWidth() { return m_wndWidth; }
	size_t GetWndHeight() { return m_wndHeight; }
	UINT32* GetFramebuffer() { return m_framebuffer; }
	float* GetZbuffer() { return m_zbuffer; }

	static App* GetInstance() {
		if (!m_instance)
		{
			m_instance = new App();
		}
		return m_instance;
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
		/*
		m_framebuffer = (UINT32*)malloc(m_wndWidth * m_wndHeight * sizeof(UINT32));
		if (!m_framebuffer)
		{
			return false;
		}
		m_zbuffer = (float*)malloc(m_wndWidth * m_wndHeight * sizeof(float));
		if (!m_zbuffer)
		{
			free(m_framebuffer);
			m_framebuffer = NULL;
			return false;
		}
		*/
		
		HDC hDC = GetDC(m_hwnd);
		m_hCompatibleDC = CreateCompatibleDC(hDC);
		ReleaseDC(m_hwnd, hDC);

		BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), m_wndWidth, m_wndHeight, 1, 32, BI_RGB, m_wndWidth * m_wndHeight * sizeof(UINT32), 0, 0, 0, 0 } };
		m_hBitmap = CreateDIBSection(m_hCompatibleDC, &bi, DIB_RGB_COLORS, (void**)&m_framebuffer, 0, 0);
		m_hOldBitmap = (HBITMAP)SelectObject(m_hCompatibleDC, m_hBitmap);
		
		return true;
	}
	virtual void Render() {
		srand(std::time(NULL));
		UCHAR R = 0, G = 0, B = (rand() % 16) * 16;
		UINT32 c = RGB(B, G, R);
		for (int i = 0; i < m_wndWidth * m_wndHeight; ++i)
		{
			m_framebuffer[i] = c;
		}
	}
	virtual void SwapBuffer() {
		HDC hDC = GetDC(m_hwnd);
		BitBlt(hDC, 0, 0, m_wndWidth, m_wndHeight, m_hCompatibleDC, 0, 0, SRCCOPY);
		ReleaseDC(m_hwnd, hDC);
	}
	virtual void GameMain() {
		Start_Clock();
		
		Render();

		SwapBuffer();
		
		Wait_Clock(30);
	}
	virtual void GameShutdown() {
		
		if (m_hCompatibleDC)
		{
			if (m_hOldBitmap)
			{
				SelectObject(m_hCompatibleDC, m_hOldBitmap);
				m_hOldBitmap = NULL;
			}
			DeleteDC(m_hCompatibleDC);
			m_hCompatibleDC = NULL;
		}
		if (m_hBitmap)
		{
			DeleteObject(m_hBitmap);
			m_hBitmap = NULL;
		}
		
		/*
		if (m_framebuffer != NULL)
		{
			free(m_framebuffer);
			m_framebuffer = NULL;
		}
		if (m_zbuffer != NULL)
		{
			free(m_zbuffer);
			m_zbuffer = NULL;
		}
		*/
	}
};

App* App::m_instance = NULL;

App *gApp = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	gApp = App::GetInstance();
	if (gApp->InitWindow(std::tstring(TEXT("Qbic")), std::tstring(TEXT("Qbic")), hInstance, WndProc, 1024, 768))
	{
		gApp->Run();
	}
	delete gApp;
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
