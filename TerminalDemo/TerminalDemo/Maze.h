#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

class Maze {
public:
    Maze(int width, int height); // 构造函数
    void generateMaze(); // 生成迷宫
    void displayMaze() const; // 显示迷宫
    void move(char direction); // 移动函数
    bool isAtExit() const; // 检查是否到达终点

private:
    int width; // 迷宫宽度
    int height; // 迷宫高度
    std::vector<std::vector<char>> maze; // 迷宫数据结构
    int playerX; // 玩家X坐标
    int playerY; // 玩家Y坐标

    void initializeMaze(); // 初始化迷宫
    void carvePath(int x, int y); // 开始挖掘路径
    bool isValidMove(int x, int y) const; // 检查移动是否合法
};

#endif // MAZE_H