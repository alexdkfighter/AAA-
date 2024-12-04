// AAA-.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <string>

#include "start_print.h"

int main()
{
    std::string in;
    start_print start;
    start.start_show();//模拟终端启动
    system("cls\n");
    start.menu();//开始菜单
    while (1)
    {
        std::cin >> in;
        if (in == "1")
        {
            //重新开始游戏部分
        }
        else if (in == "2")
        {
            //存档返回（不确定是否有存档功能）
        }
        else if (in == "3")
        {
            break;
        }
        else
        {
            //显示提示后等待输入，接收输入后重新显示菜单
            std::cout << "能不能好好输入！\n";
            std::cin >> in;
            system("cls\n");
            start.menu();
        }
    }
}

