#include <windows.h>

#define UNICODE

LRESULT CALLBACK windowprocessforwindow1(HWND main_handle, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowprocessforwindow2(HWND params_handle, UINT message, WPARAM wParam, LPARAM lParam);

HWND list_box;
HWND width_box;
enum class buttons
{
exit,
};


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
bool endprogram = false;


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
main_class.lpszClassName = "windowclass 1";
main_class.lpszMenuName = NULL;
main_class.style = CS_HREDRAW | CS_VREDRAW;

if (!RegisterClassEx(&main_class))
{
int nResult = GetLastError();
MessageBox(NULL,
"Window class creation failed",
"Window Class Failed",
MB_ICONERROR);
}

HWND main_handle = CreateWindowEx(NULL,
main_class.lpszClassName,
"prakt2",
WS_OVERLAPPEDWINDOW,
0,
150,
1150,
800,
NULL,
NULL,
hInst,
NULL
);

if (main_handle == NULL)
{
int nResult = GetLastError();

MessageBox(NULL,
"Window creation failed",
"Window Creation Failed",
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
params_class.lpszClassName = "window class2";
params_class.lpszMenuName = NULL;
params_class.style = CS_HREDRAW | CS_VREDRAW;

if (!RegisterClassEx(&params_class))
{
int nResult = GetLastError();
MessageBox(NULL,
"Window class creation failed for window 2",
"Window Class Failed",
MB_ICONERROR);
}

HWND params_handle = CreateWindowEx(NULL,
params_class.lpszClassName,
"params",
NULL,
1200,
150,
400,
200,
main_handle,
NULL,
hInst,
NULL);

if (params_handle == NULL)
{
int nResult = GetLastError();

MessageBox(NULL,
"Window creation failed",
"Window Creation Failed",
MB_ICONERROR);
}

auto button_exit = CreateWindow("button", "Exit", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 1000, 700, 100, 22, main_handle, (HMENU)buttons::exit, NULL, NULL);

list_box = CreateWindow("listbox", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | LBS_NOTIFY,
50, 50, 100, 50, params_handle, NULL, NULL, NULL);
SendMessage(list_box, LB_ADDSTRING, NULL, (LPARAM)"red");
SendMessage(list_box, LB_ADDSTRING, NULL, (LPARAM)"green");
SendMessage(list_box, LB_ADDSTRING, NULL, (LPARAM)"yellow");
SendMessage(list_box, LB_SETCURSEL, (WPARAM)0, NULL);

width_box = CreateWindow("listbox", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | LBS_NOTIFY,
155, 50, 100, 50, params_handle, NULL, NULL, NULL);
SendMessage(width_box, LB_SETITEMDATA, SendMessage(width_box, LB_ADDSTRING, NULL, (LPARAM)"3"), 3);
SendMessage(width_box, LB_SETITEMDATA, SendMessage(width_box, LB_ADDSTRING, NULL, (LPARAM)"6"), 6);
SendMessage(width_box, LB_SETITEMDATA, SendMessage(width_box, LB_ADDSTRING, NULL, (LPARAM)"9"), 9);
SendMessage(width_box, LB_SETCURSEL, (WPARAM)0, NULL);


ShowWindow(params_handle, nShowCmd);

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
static HPEN hPen = NULL;
static
BOOL fDraw = FALSE;
static POINT ptPrevious = { 0 };
HDC hdc;
switch (msg)
{
case WM_PAINT:
{
PAINTSTRUCT ps;
HDC hdc = BeginPaint(handleforwindow, &ps);
SelectObject(hdc, GetStockObject(DC_BRUSH));
FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

EndPaint(handleforwindow, &ps);
break;
}
case WM_LBUTTONDOWN:
fDraw = TRUE;
ptPrevious.x = LOWORD(lParam);
ptPrevious.y = HIWORD(lParam);
break;
case WM_LBUTTONUP:
if (fDraw)
{
hdc = GetDC(handleforwindow);
MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);
LineTo(hdc, LOWORD(lParam), HIWORD(lParam));
ReleaseDC(handleforwindow, hdc);
fDraw = FALSE;
}
break;
case WM_MOUSEMOVE:
if (fDraw)
{
hdc = GetDC(handleforwindow);
HPEN pen;
pen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
auto index = SendMessage(list_box, LB_GETCURSEL, 0, 0);
auto index_width = SendMessage(width_box, LB_GETCURSEL, 0, 0);
auto data = SendMessage(width_box, LB_GETITEMDATA, index_width, 0);
if (index == 0)
pen = CreatePen(PS_SOLID, data, RGB(255, 0, 0));
else if (index == 1)
pen = CreatePen(PS_SOLID, data, RGB(0, 128, 0));
else if (index == 2)
pen = CreatePen(PS_SOLID, data, RGB(255, 255, 0));
SelectObject(hdc, pen);
MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);
LineTo
(
hdc,
ptPrevious.x = LOWORD(lParam),
ptPrevious.y = HIWORD(lParam)
);
ReleaseDC(handleforwindow, hdc);
}
break;
case WM_COMMAND:
{
if ((buttons)wParam == buttons::exit)
PostQuitMessage(0);
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
switch (msg)
{
case WM_DESTROY:
{

break;
}
}
return DefWindowProc(handleforwindow, msg, wParam, lParam);
}