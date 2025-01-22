/*int main() {
	SetConsoleOutputCP(936);
	TerminalMockup terminal(".");
	terminal.run();
}*/

#include "CountdownWindow.h"

int main() {
	CountdownWindow window(60); // 创建倒计时窗口，倒计时60秒
	window.Run();              // 启动消息循环
	return 0;
}