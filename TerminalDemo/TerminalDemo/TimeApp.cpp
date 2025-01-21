#include "TimeApp.h"
#include <atomic>
#include <thread>
#include <iostream>

std::atomic<bool> countdownStarted(false);
int globalTime = 30;
int globalStart = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hButton; // 按钮句柄

    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_CREATE:
        // 创建按钮并保存句柄
        hButton = CreateWindow(
            L"BUTTON",  // 按钮类名
            L"开始", // 按钮文本
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // 样式
            50,         // x位置
            100,        // y位置
            200,        // 宽度
            50,         // 高度
            hwnd,       // 父窗口
            (HMENU)1,   // 按钮ID
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL);      // 附加参数
        return 0;
    case WM_COMMAND: // 处理按钮点击事件
        if (LOWORD(wParam) == 1) { // 如果按钮被点击
            if (!countdownStarted) {
                countdownStarted = true;
                ShowWindow(hButton, SW_HIDE); // 隐藏按钮
                globalStart = 1; // 在命令行输出信息

                // 启动倒计时线程
                std::thread([hwnd]() {
                    int totalSeconds = globalTime; // time秒倒计时
                    while (totalSeconds >= 0) {
                        // 在窗口中显示倒计时
                        std::wstring timeString = L"倒计时还剩: " +
                            std::to_wstring(totalSeconds / 60) + L":" +
                            (totalSeconds % 60 < 10 ? L"0" : L"") + std::to_wstring(totalSeconds % 60);

                        // 使用 SetWindowText 更新窗口文本
                        SetWindowText(hwnd, timeString.c_str());
                        Sleep(1000); // 暂停1秒
                        totalSeconds--;
                    }

                    SetWindowText(hwnd, L"倒计时结束!");
                    Sleep(2000); // 显示2秒结束信息

                    // 结束后重置状态
                    countdownStarted = false; // 这里可以设置一个全局变量来重置状态
                    }).detach(); // 启动线程并分离
            }
        }
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int TimeStart(int stime) {
    globalTime = stime;

    // 创建窗口类
    const wchar_t CLASS_NAME[] = L"TimerWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // 创建窗口
    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"倒计时", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
        NULL, NULL, wc.hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, SW_SHOW);

    // 创建新的控制台窗口
    AllocConsole();
    FILE* stream;
    freopen_s(&stream, "CONOUT$", "w", stdout);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (stream) fclose(stream); // 关闭文件流
    FreeConsole(); // 释放新控制台

    return 0;
}