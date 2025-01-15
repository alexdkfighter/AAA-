// TerminalDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "cmd_print.h"
#include "Maze.h"
#include <conio.h> // 包含 _getch() 函数的头文件

int main() {
    // 示例 1: 使用系统生成的迷宫
    int width = 21;
    int height = 21;
    Maze maze1(width, height, MazeType::GENERATED);

    char command;
    while (true) {
        system("cls");
        maze1.displayMaze();
        std::cout << "请输入移动方向 (w: 上, s: 下, a: 左, d: 右, q: 退出): ";
        command = _getch(); // 使用 _getch() 获取单个字符输入
        if (maze1.move(command)) {
            break;
        }
    }

    // 示例 2: 使用用户提供的迷宫
    std::vector<std::vector<char>> providedMaze = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };

    width = 11;
    height = 7;

    Maze maze2(width, height, MazeType::PROVIDED, providedMaze);

    while (true) {
        system("cls");
        maze2.displayMaze();
        std::cout << "请输入移动方向 (w: 上, s: 下, a: 左, d: 右, q: 退出): ";
        command = _getch(); // 使用 _getch() 获取单个字符输入
        if (maze2.move(command)) {
            break;
        }
    }

    // 继续用户输入和移动逻辑...
}