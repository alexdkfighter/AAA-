#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>

extern std::atomic<bool> countdownStarted; // 倒计时状态标志

extern int globalTime;
extern int globalStart;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int TimeStart(int stime);