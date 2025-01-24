#ifndef COUNTDOWNWINDOW_H
#define COUNTDOWNWINDOW_H

#include <windows.h>
#include <string>
#include <sstream>

class CountdownWindow {
private:
    HWND hwnd;                // 窗口句柄
    HINSTANCE hInstance;      // 实例句柄
    int remainingSeconds;     // 剩余秒数
    bool isCountdownComplete; // 倒计时是否完成

    // 静态窗口过程和定时器回调
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

    // 消息处理函数
    void OnPaint();
    void OnDestroy();

public:
    // 构造函数和析构函数
    CountdownWindow(int seconds = 60);
    ~CountdownWindow();

    // 启动消息循环
    void Run();
};

#endif // COUNTDOWNWINDOW_H
