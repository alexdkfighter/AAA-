#pragma once

#include <windows.h>
#include <vector>
#include <string>

class TextLine {
public:
    std::wstring text;
    size_t currentChar = 0;
    bool isComplete = false;

    TextLine(const std::wstring& str) : text(str) {}
};

class TextTerminal {
public:
    HWND hwnd;
    std::vector<TextLine> lines;
    size_t currentLineIndex = 0;
    static const int CHAR_DELAY = 100; // Ã¿¸ö×Ö·ûµÄÑÓ³Ù

    TextTerminal(const std::vector<std::wstring>& inputLines);
    void run();

private:
    static VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void InitializeLines(const std::vector<std::wstring>& inputLines);
    void SetTimerForLines();
};
