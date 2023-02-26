#include <windows.h>
#include <gdiplus.h>

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);
void draw(HDC hdc);
LRESULT CALLBACK WindowProcessMessages2(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);
HWND hwndA;
HWND hwndB;
int width;
int height;
int circle_diameter = 100;
int x, y;

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
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		nullptr, nullptr, currentInstance, nullptr);

	hwndB = CreateWindow(name, L"prakt6",
		WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		hwndA, nullptr, currentInstance, nullptr);
	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, param, lparam);
	}
}

LRESULT CALLBACK WindowProcessMessages2(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) {
	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg) {
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
		circle_diameter += 10;
		hdc = GetDC(hwndB);
		draw(hdc);
		ReleaseDC(hwndB, hdc);
		break;
	}
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		draw(hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, param, lparam);
	}
}


void draw(HDC hdc) {
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));
	gf.DrawEllipse(&pen, width/2 - circle_diameter / 2, height/2-circle_diameter/2, circle_diameter, circle_diameter);
}