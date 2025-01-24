/*int main() {
	SetConsoleOutputCP(936);
	TerminalMockup terminal(".");
	terminal.run();
}*/

#include "TerminalMockup.h"
int main() {
	TerminalMockup terminal(".\\terminal\\D");
	terminal.findBoss();
	terminal.run();
}