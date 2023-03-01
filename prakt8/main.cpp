#include <windows.h>
#include <windowsx.h>
#include <string>

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);
HWND hwndA;
enum class menu
{
	prog1,
	prog2,
	prog3,
	prog4,
	prog5,
	prog6,
	prog7,
	button,
	info,
	exit,
};

int width, height = 100;
std::wstring history;
HWND static_box;

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount) {

	TCHAR CLASS_NAME [] = L"myWin32WindowClass";
	WNDCLASS wc{};
	wc.hInstance = currentInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcessMessages;
	RegisterClass(&wc);

	hwndA = CreateWindow(CLASS_NAME, L"prakt8",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0,
		800, 600,
		nullptr, nullptr, currentInstance, nullptr);

	CreateWindow(L"button", L"�������", WS_VISIBLE | WS_CHILD, 10, 10, 70, 20, hwndA, (HMENU)menu::button, currentInstance, NULL);

	HANDLE hIcon = LoadImage(0, L"G:\\�����\\�����������\\icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (hIcon) {
		//Change both icons to the same icon handle.
		SendMessage(hwndA, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
		SendMessage(hwndA, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	}

	HMENU menu = CreateMenu();
	HMENU popmenu = CreatePopupMenu();
	AppendMenu(menu, MF_STRING | MF_POPUP, (UINT_PTR)popmenu, L"&���������");
	AppendMenu(menu, MF_STRING, (UINT_PTR)menu::info, L"&����������");
	AppendMenu(popmenu, MF_STRING, (UINT_PTR)menu::prog1, L"&������1");
	AppendMenu(popmenu, MF_STRING, (UINT_PTR)menu::prog2, L"&������2");
	AppendMenu(popmenu, MF_STRING, (UINT_PTR)menu::prog3, L"&������3");
	AppendMenu(popmenu, MF_STRING, (UINT_PTR)menu::prog4, L"&������4");
	AppendMenu(popmenu, MF_STRING, (UINT_PTR)menu::prog5, L"&������5");
	AppendMenu(popmenu, MF_STRING, (UINT_PTR)menu::prog6, L"&������6");
	AppendMenu(popmenu, MF_STRING, (UINT_PTR)menu::prog7, L"&������7");
	AppendMenu(popmenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(popmenu, MF_STRING, (UINT_PTR)menu::exit, L"&�����");

	SetMenu(hwndA, menu);

	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) {
	switch (msg) {

	case WM_SIZE:
	{
		width = LOWORD(lparam);
		height = HIWORD(lparam);
		MoveWindow(static_box, (width / 2 - 100), (height / 2 - 10), 200, 20, TRUE);
		break;
	}
	case WM_CREATE:
	{
		static_box = CreateWindow(L"static", L"������������.", WS_CHILD | WS_VISIBLE, (width / 2 - 100), (height / 2 - 10), 200, 20, hwnd, NULL, (HINSTANCE)GetModuleHandle(NULL), NULL);
		break;
	}
	case WM_COMMAND:
	{
		if ((menu)param == menu::exit)
		{
			PostQuitMessage(0);
			break;
		}
		else if ((menu)param == menu::info)
		{
			std::wstring text = L"����� ��������� ���������� ��-31.\n\
��������������� � ������������ ��������.\n\
������ 1 - ���������� ������ ��� ������ MSPaint � WinCalc\n\
������ 2 - ��������� � ���� �������� ����\n\
������ 3 - ����������� ������� ������� ����������\n\
������ 4 - ������������ ���������� � �������� ���� �� ������ �������������� � ������� ����\n\
������ 5 - ���������� - ������ �� �������\n\
������ 6 - ����������� ��������� ����������\n\
������ 7 - �������� ����� BMP ��� ������� ���� ����";
			MessageBox(hwndA, text.c_str(), L"����������", MB_OK | MB_ICONINFORMATION);
		}
		else if ((menu)param == menu::button)
		{
			MessageBox(hwndA, history.c_str(), L"�������", MB_OK | MB_ICONINFORMATION);
		}
		else if ((menu)param == menu::prog1)
		{
			WinExec("G:\\�������\\module1\\x64\\Debug\\prakt1.exe", 1);
			history += L"��� ������ ������ 1\n";
		}
		else if ((menu)param == menu::prog2)
		{
			WinExec("G:\\�������\\module2\\build\\Debug\\prakt2.exe", 1);
			history += L"��� ������ ������ 2\n";
		}
		else if ((menu)param == menu::prog3)
		{
			WinExec("G:\\�������\\module3\\build\\Debug\\prakt3.exe", 1);
			history += L"��� ������ ������ 3\n";
		}
		else if ((menu)param == menu::prog4)
		{
			WinExec("G:\\�������\\module4\\build\\Debug\\prakt4.exe", 1);
			history += L"��� ������ ������ 4\n";
		}
		else if ((menu)param == menu::prog5)
		{
			WinExec("G:\\�������\\module5\\build\\Debug\\prakt5.exe", 1);
			history += L"��� ������ ������ 5\n";
		}
		else if ((menu)param == menu::prog6)
		{
			WinExec("G:\\�������\\module6\\build\\Debug\\prakt6.exe", 1);
			history += L"��� ������ ������ 6\n";
		}
		else if ((menu)param == menu::prog7)
		{
			WinExec("G:\\�������\\module7\\build\\Debug\\prakt7.exe", 1);
			history += L"��� ������ ������ 7\n";
		}
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, param, lparam);
	}
}
