#include <windows.h>
#include <string>
#include <vector>


TCHAR czClassName[] = L"myClass";
TCHAR class_name[] = L"second";
TCHAR czFormName[] = L"prakt5";
HWND hwndA;
HWND hwndB;
HWND button1;
HWND button2;
HWND button3;
HWND but1;
HWND but2;
HWND but3;
HWND cancel;



enum class menu
{
    exit,
    help,
    button1,
    button2,
    button3,
    but1,
    but2,
    but3,
    cancel,
};


LRESULT CALLBACK WndProc2(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_COMMAND)
    {
        ShowWindow(hwndB, SW_HIDE);
        DestroyWindow(but1);
        DestroyWindow(but2);
        DestroyWindow(but3);
        DestroyWindow(cancel);
        if ((menu)wParam == menu::but1)
        {
            SendMessage(hwndA, WM_COMMAND, (WPARAM)menu::button1, NULL);
        }
        else if ((menu)wParam == menu::but2)
        {
            SendMessage(hwndA, WM_COMMAND, (WPARAM)menu::button2, NULL);
        }
        else if ((menu)wParam == menu::but3)
        {
            SendMessage(hwndA, WM_COMMAND, (WPARAM)menu::button3, NULL);
        }

    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

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
        break;
    }
    case WM_COMMAND:
    {
        if ((menu)wParam == menu::exit)
        {
            PostQuitMessage(0);
        }
        else if ((menu)wParam == menu::help)
        {
            std::wstring text = L"В этой программе можно выбрать вопросы и отвечать на них.\n"\
                L"При нажатии кнопки Выход в пункте меню Файл можно закрыть программу.\n"\
                L"При нажатии кнопки Помощь открывается данное окно.\n"\
                L"Чтобы выбрать вопрос необходимо нажать на одну из кнопкок с номером вопроса.";
            MessageBox(hwndA, text.c_str(), L"Помощь", MB_OK | MB_ICONINFORMATION);

        }
        else if ((menu)wParam == menu::button1)
        {
            auto id = MessageBox(hwndA, L"Великая отественная война началась в 1941?", L"Вопрос 1", MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES)
            {
                ShowWindow(hwndB, SW_SHOW);
                but2 = CreateWindow(L"button", L"Вопрос 2", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 20, 200, 100, 22, hwndB, (HMENU)menu::but2, NULL, NULL);
                but3 = CreateWindow(L"button", L"Вопрос 3", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 120, 200, 100, 22, hwndB, (HMENU)menu::but3, NULL, NULL);
                cancel = CreateWindow(L"button", L"Отмена", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 220, 200, 100, 22, hwndB, (HMENU)menu::cancel, NULL, NULL);
            }
            else if (id == IDNO)
            {
                MessageBox(hwndA, L"Ответ неверный!", L"", MB_OK | MB_ICONERROR);
            }
        }
        else if ((menu)wParam == menu::button2)
        {
            auto id = MessageBox(hwndA, L"На значке BMW изображен зонт?", L"Вопрос 2", MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES)
            {
                MessageBox(hwndA, L"Ответ неверный!", L"", MB_OK | MB_ICONERROR);
            }
            else if (id == IDNO)
            {
                ShowWindow(hwndB, SW_SHOW);
                but1 = CreateWindow(L"button", L"Вопрос 1", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 20, 200, 100, 22, hwndB, (HMENU)menu::but1, NULL, NULL);
                but3 = CreateWindow(L"button", L"Вопрос 3", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 120, 200, 100, 22, hwndB, (HMENU)menu::but3, NULL, NULL);
                cancel = CreateWindow(L"button", L"Отмена", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 220, 200, 100, 22, hwndB, (HMENU)menu::cancel, NULL, NULL);
            }
        }
        else if ((menu)wParam == menu::button3)
        {
            auto id = MessageBox(hwndA, L"Трава зеленая?", L"Вопрос 3", MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES)
            {
                ShowWindow(hwndB, SW_SHOW);
                but1 = CreateWindow(L"button", L"Вопрос 1", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 20, 200, 100, 22, hwndB, (HMENU)menu::but1, NULL, NULL);
                but2 = CreateWindow(L"button", L"Вопрос 2", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 120, 200, 100, 22, hwndB, (HMENU)menu::but2, NULL, NULL);
                cancel = CreateWindow(L"button", L"Отмена", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 220, 200, 100, 22, hwndB, (HMENU)menu::cancel, NULL, NULL);
            }
            else if (id == IDNO)
            {
                MessageBox(hwndA, L"Ответ неверный!", L"", MB_OK | MB_ICONERROR);
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

    WNDCLASS cw;

    cw.style = CS_VREDRAW | CS_HREDRAW;
    cw.cbClsExtra = 0;
    cw.cbWndExtra = 0;
    cw.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    cw.hCursor = LoadCursor(NULL, IDC_ARROW);
    cw.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    cw.hInstance = hInst;
    cw.lpfnWndProc = WndProc2;
    cw.lpszClassName = class_name;
    cw.lpszMenuName = NULL;

    RegisterClass(&cw);

    hwndB = CreateWindow(
        class_name,
        czFormName,
        NULL,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        500,
        300,
        NULL,
        NULL,
        hInst,
        NULL);

    HWND static_text = CreateWindow(L"static", L"Ответ верный. Выберите действие", WS_CHILD | WS_VISIBLE, 20, 100, 240, 20, hwndB, NULL, hInst, NULL);

    ShowWindow(hwndB, SW_HIDE);


    button1 = CreateWindow(L"button", L"Вопрос 1", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 300, 400, 100, 22, hwndA, (HMENU)menu::button1, NULL, NULL);
    button2 = CreateWindow(L"button", L"Вопрос 2", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 500, 400, 100, 22, hwndA, (HMENU)menu::button2, NULL, NULL);
    button3 = CreateWindow(L"button", L"Вопрос 3", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_PUSHBUTTON, 700, 400, 100, 22, hwndA, (HMENU)menu::button3, NULL, NULL);


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


    HMENU hmenu1;
    hmenu1 = CreateMenu();
    HMENU popmenu;
    popmenu = CreatePopupMenu();

    AppendMenu(hmenu1, MF_STRING | MF_POPUP, (UINT_PTR)popmenu, L"&Файл");
    AppendMenu(hmenu1, MF_STRING, (UINT)menu::help, L"&Помощь");
    
    AppendMenu(popmenu, MF_STRING, (UINT)menu::exit, L"Выход");

    SetMenu(hwndA, hmenu1);


    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}