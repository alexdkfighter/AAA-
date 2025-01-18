#include "TextTerminal.h"

VOID CALLBACK TextTerminal::TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    TextTerminal* terminal = reinterpret_cast<TextTerminal*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (terminal->currentLineIndex < terminal->lines.size()) {
        TextLine& currentLine = terminal->lines[terminal->currentLineIndex];

        if (currentLine.currentChar < currentLine.text.length()) {
            currentLine.currentChar++;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        else {
            currentLine.isComplete = true;
            if (terminal->currentLineIndex < terminal->lines.size() - 1) {
                terminal->currentLineIndex++;
            }
        }
    }
    else {
        KillTimer(hwnd, idEvent);
    }
}

LRESULT CALLBACK TextTerminal::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    TextTerminal* terminal = reinterpret_cast<TextTerminal*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (terminal == nullptr && uMsg == WM_NCCREATE) {
        terminal = reinterpret_cast<TextTerminal*>(((LPCREATESTRUCT)lParam)->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(terminal));
        terminal->hwnd = hwnd;
    }

    if (terminal != nullptr) {
        switch (uMsg) {
        case WM_CREATE: {
            terminal->InitializeLines();
            terminal->SetTimerForLines();
            return 0;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // 设置文本属性
            SetTextColor(hdc, RGB(0, 0, 0));
            SetBkMode(hdc, TRANSPARENT);

            HFONT hFont = CreateFont(
                30, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_DONTCARE, L"微软雅黑"
            );

            SelectObject(hdc, hFont);

            // 逐字显示文本
            int yPos = 50;
            for (size_t i = 0; i < terminal->lines.size(); i++) {
                if (i <= terminal->currentLineIndex) {
                    std::wstring partialText = terminal->lines[i].text.substr(0, terminal->lines[i].currentChar);
                    TextOutW(hdc, 50, yPos, partialText.c_str(), static_cast<int>(partialText.length()));
                }
                yPos += 50;
            }

            DeleteObject(hFont);
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void TextTerminal::InitializeLines() {
    lines.push_back(TextLine(L"我是D我会给你帮助"));
    lines.push_back(TextLine(L"我会教你一些基本命令"));
    lines.push_back(TextLine(L"我相信你一定能跑出去的"));
}

void TextTerminal::SetTimerForLines() {
    SetTimer(hwnd, 1, CHAR_DELAY, TimerProc);
}

TextTerminal::TextTerminal() {
    // 创建窗口类
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"TextWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassEx(&wc);

    // 创建窗口
    hwnd = CreateWindowEx(
        0, L"TextWindow", L"D",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 300,
        NULL, NULL, GetModuleHandle(NULL), this
    );

    // 显示窗口
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

void TextTerminal::run() {
    // 消息循环
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}