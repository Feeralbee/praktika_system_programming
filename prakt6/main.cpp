#include <windows.h>
#include <gdiplus.h>
LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);
void draw(HDC hdc);
LRESULT CALLBACK WindowProcessMessages2(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);
HWND hwndA;
HWND hwndB;
HWND button;
int width;
int height;
int circle_diameter = 80;
int x, y;
enum class buttons
{
	color = 0,
	radio1,
	radio2,
	radio3,
	ok,
};
auto color = Gdiplus::Color(255, 0, 0, 0);
auto temp_color = Gdiplus::Color(255, 0, 0, 0);
int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount) {
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	TCHAR CLASS_NAME [] = L"myWin32WindowClass";
	WNDCLASS wc{};
	wc.hInstance = currentInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcessMessages;
	RegisterClass(&wc);
	TCHAR name[] = L"second";
	WNDCLASS wndclass{};
	wndclass.hInstance = currentInstance;
	wndclass.lpszClassName = name;
	wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndclass.lpfnWndProc = WindowProcessMessages2;
	RegisterClass(&wndclass);
	hwndA = CreateWindow(CLASS_NAME, L"prakt6",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0,
		800, 600,
		nullptr, nullptr, currentInstance, nullptr);
	button = CreateWindow(L"button", L"цвет", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 10, 10, 50, 20, hwndA, (HMENU)buttons::color, currentInstance, NULL);
	hwndB = CreateWindow(name, L"prakt6",
		WS_VISIBLE,
		810, 0,
		400, 300,
		hwndA, nullptr, currentInstance, nullptr);
	ShowWindow(hwndB, SW_HIDE);
	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}
LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) {
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg) {
	case WM_COMMAND:
	{
		if ((buttons)param == buttons::color)
		{
			ShowWindow(hwndB, SW_SHOW);
		}
		break;
	}
	case WM_CREATE:
	{
		SetTimer(hwnd, 1, 100, NULL);
		break;
	}
	case WM_SIZE:
	{
		width = LOWORD(lparam);
		height = HIWORD(lparam);
		break;
	}
	case WM_TIMER:
	{
		InvalidateRect(hwndA, NULL, TRUE);
		UpdateWindow(hwndA);
		circle_diameter += 10;
		if (circle_diameter >= width || circle_diameter >= height)
			circle_diameter = -circle_diameter;
		hdc = GetDC(hwndA);
		draw(hdc);
		ReleaseDC(hwndA, hdc);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, param, lparam);
	}
}
LRESULT CALLBACK WindowProcessMessages2(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) {
	switch (msg) 
	{
	case WM_CREATE:
	{
		auto rad = CreateWindow(L"button", L"blue",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10, 10, 80, 30, hwnd, (HMENU)buttons::radio1, (HINSTANCE)GetModuleHandle(NULL), NULL);
		CreateWindow(L"button", L"red",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10, 30, 80, 30, hwnd, (HMENU)buttons::radio2, (HINSTANCE)GetModuleHandle(NULL), NULL);
		CreateWindow(L"button", L"green",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10, 50, 80, 30, hwnd, (HMENU)buttons::radio3, (HINSTANCE)GetModuleHandle(NULL), NULL);
		CreateWindow(L"button", L"ok",
			WS_CHILD | WS_VISIBLE,
			10, 80, 80, 30, hwnd, (HMENU)buttons::ok, (HINSTANCE)GetModuleHandle(NULL), NULL);
		break;
	}
	case WM_COMMAND:
	{
		if ((buttons)param == buttons::radio1)
		{
			temp_color = Gdiplus::Color(255, 0, 0, 139);
		}
		else if ((buttons)param == buttons::radio2)
		{
			temp_color = Gdiplus::Color(255, 255, 0, 0);
		}
		else if ((buttons)param == buttons::radio3)
		{
			temp_color = Gdiplus::Color(255, 124, 255, 0);
		}
		else if ((buttons)param == buttons::ok)
		{
			color = temp_color;
		}
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, param, lparam);
	}
}


void draw(HDC hdc) {
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(color);
	gf.DrawEllipse(&pen, width/2 - circle_diameter / 2, height/2-circle_diameter/2, circle_diameter, circle_diameter);
}