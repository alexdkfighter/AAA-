// AAA-.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include "start_print.h"
#include "cmd_print.h"

int main()
{
    start_print start;
    start.start_show();//模拟终端启动
    system("cls\n");
    start.menu();//开始菜单
    while (1)
    {
        char in = _getch();//直接获取按键
        if (in == '1')
        {
            start.running = 0;
            //重新开始游戏部分
        }
        else if (in == '2')
        {
            start.running = 0;
            //存档返回（不确定是否有存档功能）
        }
        else if (in == '3')
        {
            break;
        }
        else
        {
            //我们选用按键，而不是输入然后回车
        }
    }
}

