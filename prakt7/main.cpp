#pragma comment (lib, "gdiplus.lib")
#include <windows.h>
#include <string>
#include <vector>
#include <gdiplus.h>

TCHAR czClassName[] = L"myClass";
TCHAR class_name[] = L"second";
TCHAR czFormName[] = L"prakt7";
HWND hwndA;
WCHAR path[MAX_PATH];

int width, height;

enum class menu
{
    exit = 0,
    open,
};


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        std::memset(path, 0, sizeof(path));
        break;
    }
    case WM_GETMINMAXINFO:
    {
        /*LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
        lpMMI->ptMinTrackSize.x = GetSystemMetrics(SM_CXSCREEN) / 2;
        lpMMI->ptMinTrackSize.y = GetSystemMetrics(SM_CYSCREEN) / 2;
        */break;
    }
    case WM_SIZE:
    {
        width = LOWORD(lParam);
        height = HIWORD(lParam);
        if (path != NULL)
        {
            InvalidateRect(hwndA, NULL, TRUE);
            UpdateWindow(hwndA);
            auto hdc = GetDC(hwndA);
            Gdiplus::Graphics gf(hdc);
            Gdiplus::Bitmap bmp(path);
            gf.DrawImage(&bmp, 0, 0, width, height);
        }

        break;
    }
    case WM_COMMAND:
    {
        if ((menu)wParam == menu::exit)
        {
            PostQuitMessage(0);
        }
        if ((menu)wParam == menu::open)
        {
            OPENFILENAME open_file_name;
            const LPCWSTR filters = L"BMP \0*.bmp\0";
            const auto flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
            ZeroMemory(&open_file_name, sizeof(OPENFILENAME));
            std::memset(path, 0, sizeof(path));
            open_file_name.lStructSize = sizeof(OPENFILENAME);
            open_file_name.hInstance = (HINSTANCE)GetStockObject(NULL);
            open_file_name.hwndOwner = NULL;
            open_file_name.lpstrFile = path;
            open_file_name.nMaxFile = MAX_PATH;
            open_file_name.lpstrFilter = filters;
            open_file_name.nFilterIndex = 1;
            open_file_name.lpstrFileTitle = NULL;
            open_file_name.nMaxFileTitle = 0;
            open_file_name.lpstrInitialDir = NULL;
            open_file_name.Flags = flags;

            if (GetOpenFileName(&open_file_name))
            {
                auto hdc = GetDC(hwndA);
                Gdiplus::Graphics gf(hdc);
                Gdiplus::Bitmap bmp(path);
                gf.DrawImage(&bmp, 0, 0, width, height);
                return 1;
            }

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
        900,
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
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    MSG msg;

    myRegistryClass(hInst, cmdShow);
    InitInstance(hInst, cmdShow);


    HMENU hmenu1;
    hmenu1 = CreateMenu();
    HMENU popmenu;
    popmenu = CreatePopupMenu();

    AppendMenu(hmenu1, MF_STRING | MF_POPUP, (UINT_PTR)popmenu, L"&Файл");

    AppendMenu(popmenu, MF_STRING, (UINT)menu::open, L"Открыть");
    AppendMenu(popmenu, MF_STRING, (UINT)menu::exit, L"Выход");

    SetMenu(hwndA, hmenu1);


    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    Gdiplus::GdiplusShutdown(gdiplusToken);
    return 0;
}