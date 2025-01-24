/*int main() {
	SetConsoleOutputCP(936);
	TerminalMockup terminal(".");
	terminal.run();
}*/

<<<<<<< HEAD

#include "TerminalMockup.h"
int main() {
	TerminalMockup terminal(".\\terminal\\D");
	terminal.findBoss();
	terminal.run();
=======
#include "CountdownWindow.h"

int main() {
	CountdownWindow window(60); // 创建倒计时窗口，倒计时60秒
	window.Run();              // 启动消息循环
	return 0;
>>>>>>> 1a916709aee4c95f97145047bd20821ea4830779
}