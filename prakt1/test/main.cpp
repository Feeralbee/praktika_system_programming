#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "resource.h"
#include <string>
#include <vector>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"task1",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 400,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
   DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), hwnd, DialogProc);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        auto hwnd_check_1 = GetDlgItem(hDlg, IDC_CHECK1);
        SendMessage(hwnd_check_1, BM_SETCHECK, BST_CHECKED, 0);
        auto hwnd_check_2 = GetDlgItem(hDlg, IDC_CHECK2);
        SendMessage(hwnd_check_2, BM_SETCHECK, BST_CHECKED, 0);

    }
    case WM_COMMAND:
    {
        if (wParam == IDMYOK)
        {
            auto hwnd = GetDlgItem(hDlg, IDC_EDIT);
            int len = GetWindowTextLength(hwnd) + 1;
            std::vector<wchar_t> buf(len);
            GetWindowText(hwnd, &buf[0], len);
            std::wstring command = &buf[0];
            if (command == L"paint")
            {
                WinExec("mspaint.exe", 1);
            }
            else if (command == L"calculator")
                WinExec("calc.exe", 1);
            else
            {
                MessageBox(hDlg, L"¬ведите paint или calculator", L"ќшибка", MB_OK);
            }
        }
        else if (wParam == IDC_CHECK1) //visible
        {
            auto hwnd = GetDlgItem(hDlg, IDC_CHECK1);
            auto res = SendMessage(hwnd, BM_GETCHECK, 0, 0);
            if (res == BST_CHECKED)
            {
                auto hwnd_edit = GetDlgItem(hDlg, IDC_EDIT);
                ShowWindow(hwnd_edit, SW_SHOW);

            }
            else if (res == BST_UNCHECKED)
            {
                auto hwnd_edit = GetDlgItem(hDlg, IDC_EDIT);
                ShowWindow(hwnd_edit, SW_HIDE);
            }
        }
        else if (wParam == IDC_CHECK2)
        {
            auto hwnd = GetDlgItem(hDlg, IDC_CHECK2);
            auto res = SendMessage(hwnd, BM_GETCHECK, 0, 0);
            if (res == BST_CHECKED)
            {
                SendDlgItemMessage(hDlg, IDC_EDIT, EM_SETREADONLY, FALSE, 0);

            }
            else if (res == BST_UNCHECKED)
            {
                SendDlgItemMessage(hDlg, IDC_EDIT, EM_SETREADONLY, TRUE, 0);
            }
        }
        else if (wParam == IDCANCEL)
        {
            EndDialog(hDlg, 1);
        }

    }
    }

    return 0;
}