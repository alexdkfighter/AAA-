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


//�趨�������������ɫ(12��;10��;15��)
void setColor(int color);

//ָ��ˢ��ĳ���е�����
//����ˢ��һ�����飬�ӵ�һ��ͷ��ʼˢ��
void updateLine(int line, const std::string& text);

//��ĳһ��������������룬����һ��ʱ����ʾ����
void startGarbledTextThread(int line, int color, const std::string& text, int& running, int garbledDuration, int clearDuration);

#endif