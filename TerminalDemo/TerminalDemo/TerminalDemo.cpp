#include "TerminalMockup.h"
#include <windows.h>
#include <iostream>

int main() {
	SetConsoleOutputCP(936);
	TerminalMockup terminal(".");
	terminal.run();
}