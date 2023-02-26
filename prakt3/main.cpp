#include <windows.h>
#include <xstring>

LRESULT CALLBACK windowprocessforwindow1(HWND main_handle, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowprocessforwindow2(HWND params_handle, UINT message, WPARAM wParam, LPARAM lParam);

HWND main_handle;
HWND static_cont;

enum class buttons
{
	run,
};

auto name = L"windowclass 1";

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX main_class;
	ZeroMemory(&main_class, sizeof(WNDCLASSEX));
	main_class.cbClsExtra = NULL;
	main_class.cbSize = sizeof(WNDCLASSEX);
	main_class.cbWndExtra = NULL;
	main_class.hbrBackground = (HBRUSH)COLOR_WINDOW;
	main_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	main_class.hIcon = NULL;
	main_class.hIconSm = NULL;
	main_class.hInstance = hInst;
	main_class.lpfnWndProc = (WNDPROC)windowprocessforwindow1;
	main_class.lpszClassName = name;
	main_class.lpszMenuName = NULL;
	main_class.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&main_class))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			L"Window class creation failed",
			L"Window Class Failed",
			MB_ICONERROR);
	}

	main_handle = CreateWindowEx(NULL,
		main_class.lpszClassName,
		L"prakt3",
		WS_OVERLAPPEDWINDOW,
		0,
		150,
		850,
		600,
		NULL,
		NULL,
		hInst,
		NULL
	);

	if (main_handle == NULL)
	{
		int nResult = GetLastError();

		MessageBox(NULL,
			L"Window creation failed",
			L"Window Creation Failed",
			MB_ICONERROR);
	}

	ShowWindow(main_handle, nShowCmd);

	WNDCLASSEX params_class;
	ZeroMemory(&params_class, sizeof(WNDCLASSEX));
	params_class.cbClsExtra = NULL;
	params_class.cbSize = sizeof(WNDCLASSEX);
	params_class.cbWndExtra = NULL;
	params_class.hbrBackground = (HBRUSH)COLOR_WINDOW;
	params_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	params_class.hIcon = NULL;
	params_class.hIconSm = NULL;
	params_class.hInstance = hInst;
	params_class.lpfnWndProc = (WNDPROC)windowprocessforwindow2;
	params_class.lpszClassName = L"window class2";
	params_class.lpszMenuName = NULL;
	params_class.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&params_class))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			L"Window class creation failed for window 2",
			L"Window Class Failed",
			MB_ICONERROR);
	}

	auto button_run = CreateWindow(L"button", L"run", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 600, 400, 100, 22, main_handle, (HMENU)buttons::run, NULL, NULL);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK windowprocessforwindow1(HWND handleforwindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		if ((buttons)wParam == buttons::run)
		{
			HWND params_handle = CreateWindowEx(NULL,
				name,
				L"output",
				WS_OVERLAPPEDWINDOW,
				0,
				250,
				400,
				200,
				main_handle,
				NULL,
				(HINSTANCE)GetModuleHandle(NULL),
				NULL);
			ShowWindow(params_handle, SW_NORMAL);
			static_cont = CreateWindow(L"STATIC", L"", WS_VISIBLE | WS_CHILD, CW_USEDEFAULT, CW_USEDEFAULT,
				100, 25, params_handle, NULL, NULL, NULL);
		}
		break;
	}
	case WM_KEYDOWN:
	{
		std::wstring key;
		GetKeyNameText(lParam, (LPWSTR)key.c_str(), 100);
		SetWindowText(static_cont, (LPWSTR)key.c_str());
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(handleforwindow, msg, wParam, lParam);
}

LRESULT CALLBACK windowprocessforwindow2(HWND handleforwindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(handleforwindow, msg, wParam, lParam);
}