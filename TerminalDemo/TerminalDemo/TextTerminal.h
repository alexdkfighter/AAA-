#pragma once

#include <windows.h>
#include <string>
#include <vector>

struct TextLine {
    std::wstring text;
    size_t currentChar;
    bool isComplete;
    TextLine(const wchar_t* t) : text(t), currentChar(0), isComplete(false) {}
};

class TextTerminal {
private:
    std::vector<TextLine> lines;
    size_t currentLineIndex = 0;
    const int CHAR_DELAY = 100; // Ã¿¸ö×Ö·ûÏÔÊ¾ÑÓ³Ù(ºÁÃë)
    HWND hwnd;

    static VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    void InitializeLines();
    void SetTimerForLines();

public:
    TextTerminal();
    void run();
};
