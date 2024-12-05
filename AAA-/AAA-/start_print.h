#pragma once
#ifndef START_PRINT_H
#define START_PRINT_H

class start_print
{
public:
	int running;//用于判定开头是否已经结束

	//构造函数
	start_print();

	//开头的模拟终端启动显示
	void start_show();

	//游戏开始菜单
	void menu();
};

#endif