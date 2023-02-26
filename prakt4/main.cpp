#include <windows.h>
#include <string>
#include <vector>


TCHAR czClassName[] = L"myClass";
TCHAR czFormName[] = L"prakt4";
HWND hwndA;
HWND edit;

enum class menu
{
    file,
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_GETMINMAXINFO:
    {
        LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
        lpMMI->ptMinTrackSize.x = GetSystemMetrics(SM_CXSCREEN) / 2;
        lpMMI->ptMinTrackSize.y = GetSystemMetrics(SM_CYSCREEN) / 2;
        break;
    }
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        MoveWindow(edit, ((width / 2) - 150), ((height / 2) - 10), 300, 20, TRUE);
        break;
    }
    case WM_COMMAND:
    {
        if ((menu)wParam == menu::file)
        {
            TCHAR command[1024];
            GetWindowText(edit, command, 1024);
            MessageBox(hwndA, command, L"Number", MB_OK | MB_ICONINFORMATION);
        }
            break;
    }
    case WM_DESTROY: PostQuitMessage(0); break;

    default: return DefWindowProc(hwnd, message, wParam, lParam); break;
    }
}

ATOM myRegistryClass(HINSTANCE hInst, int cmdMode)
{
    WNDCLASS cw;

    cw.style = CS_VREDRAW | CS_HREDRAW;
    cw.cbClsExtra = 0;
    cw.cbWndExtra = 0;
    cw.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    cw.hCursor = LoadCursor(NULL, IDC_ARROW);
    cw.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    cw.hInstance = hInst;
    cw.lpfnWndProc = WndProc;
    cw.lpszClassName = czClassName;
    cw.lpszMenuName = NULL;

    RegisterClass(&cw);

    return 0;
}


BOOL InitInstance(HINSTANCE hInst, int Mode)
{


    hwndA = CreateWindow(
        czClassName,
        czFormName,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        600,
        600,
        NULL,
        NULL,
        hInst,
        NULL);

    ShowWindow(hwndA, Mode);
    UpdateWindow(hwndA);

    return TRUE;
}


/*Главная функция*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int cmdShow)
{
    MSG msg;

    myRegistryClass(hInst, cmdShow);
    InitInstance(hInst, cmdShow);



    edit = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | ES_NUMBER, 142, 260, 300, 20, hwndA, NULL, hInst, NULL);

    HMENU hmenu1;
    hmenu1 = CreateMenu();
    HMENU popmenu;
    popmenu = CreatePopupMenu();

    AppendMenu(hmenu1, MF_STRING | MF_POPUP, (UINT_PTR)popmenu, L"&File");
    AppendMenu(hmenu1, MF_STRING, 1, L"&Help");
    
    AppendMenu(popmenu, MF_STRING, (UINT)menu::file, L"Show number");

    SetMenu(hwndA, hmenu1);


    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}