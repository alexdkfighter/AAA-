// TerminalDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "cmd_print.h"
#include "Maze.h"
#include <conio.h> // 包含 _getch() 所需的头文件

int main() {
    int width = 21; // 迷宫宽度
    int height = 21; // 迷宫高度
    Maze maze(width, height); // 创建迷宫对象

    char command; // 用户输入的命令
    while (true) {
        system("cls"); // 清屏
        maze.displayMaze(); // 显示迷宫
        std::cout << "请输入移动方向 (w: 上, s: 下, a: 左, d: 右, q: 退出): ";
        command = _getch(); // 获取用户输入
        maze.move(command); // 移动玩家
    }

    return 0; // 返回0，结束程序
}