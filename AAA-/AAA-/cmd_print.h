#pragma once
#ifndef CMD_PRINT_H
#define CMD_PRINT_H

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <random>


//设定命令行输出的颜色(12红;10绿;15白)
void setColor(int color);

//指定刷新某个行的文字
//允许刷新一整个块，从第一个头开始刷新
void updateLine(int line, const std::string& text);

//在某一段上随机生成乱码，并在一定时间显示正常
void startGarbledTextThread(int line, int color, const std::string& text, int& running, int garbledDuration, int clearDuration);

#endif