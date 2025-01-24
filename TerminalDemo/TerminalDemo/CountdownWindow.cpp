#include "CountdownWindow.h"

// 静态窗口过程函数
LRESULT CALLBACK CountdownWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    CountdownWindow* pWindow = nullptr;
    if (uMsg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pWindow = static_cast<CountdownWindow*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
        pWindow->hwnd = hwnd;
    }
    else {
        pWindow = reinterpret_cast<CountdownWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (pWindow) {
        switch (uMsg) {
        case WM_PAINT:
            pWindow->OnPaint();
            return 0;
        case WM_DESTROY:
            pWindow->OnDestroy();
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// 处理 WM_PAINT 消息
void CountdownWindow::OnPaint() {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // 设置文本属性
    SetTextColor(hdc, RGB(255, 0, 0));
    SetBkMode(hdc, TRANSPARENT);

    HFONT hFont = CreateFont(
        48, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, L"微软雅黑"
    );

    SelectObject(hdc, hFont);

    // 显示倒计时
    std::wstringstream ss;
    ss << remainingSeconds;
    std::wstring countdownText = ss.str();

    RECT rect;
    GetClientRect(hwnd, &rect);
    DrawTextW(hdc, countdownText.c_str(), -1, &rect,
        DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    DeleteObject(hFont);
    EndPaint(hwnd, &ps);
}

// 处理 WM_DESTROY 消息
void CountdownWindow::OnDestroy() {
    PostQuitMessage(0);
}

// 构造函数
CountdownWindow::CountdownWindow(int seconds) : remainingSeconds(seconds), isCountdownComplete(false) {
    hInstance = GetModuleHandle(NULL);

    flag = 1;
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"CountdownWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassEx(&wc);

    hwnd = CreateWindowEx(
        0,
        L"CountdownWindow",
        L"倒计时",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
        NULL, NULL, hInstance, this
    );

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    SetTimer(hwnd, 1, 1000, TimerProc);
}

// 析构函数
CountdownWindow::~CountdownWindow() {
    if (hwnd) {
        DestroyWindow(hwnd);
    }
}

// 静态定时器回调函数
VOID CALLBACK CountdownWindow::TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    CountdownWindow* pWindow = reinterpret_cast<CountdownWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (pWindow && !pWindow->isCountdownComplete) {
        if (pWindow->flag == 0 || pWindow->remainingSeconds <= 0) {
            KillTimer(hwnd, idEvent);
            pWindow->isCountdownComplete = true;
            pWindow->flag = 0; // 设置flag为0
            DestroyWindow(hwnd);
            // exit(0); // 通常不建议在此处直接终止程序
        }
        else {
            pWindow->remainingSeconds--;
            InvalidateRect(hwnd, NULL, TRUE);
        }
    }
}

// 启动消息循环
void CountdownWindow::Run() {
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0) && flag != 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}