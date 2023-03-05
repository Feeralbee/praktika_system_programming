#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "resource.h"
#include <string>
#include <vector>

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
   DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProc);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
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
            PostQuitMessage(0);
        }

    }
    }

    return 0;
}