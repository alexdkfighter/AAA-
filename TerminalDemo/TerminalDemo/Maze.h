#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <conio.h>

/// <summary>
/// 枚举表示迷宫的类型
/// </summary>
enum class MazeType {
    GENERATED, ///< 系统生成的迷宫
    PROVIDED   ///< 用户提供的迷宫
};

/// <summary>
/// 迷宫类，支持生成和显示迷宫，处理玩家移动
/// </summary>
class Maze {
public:
    /// <summary>
    /// 构造函数，初始化迷宫
    /// </summary>
    /// <param name="width">迷宫的宽度</param>
    /// <param name="height">迷宫的高度</param>
    /// <param name="type">迷宫的生成类型</param>
    /// <param name="providedMaze">用户提供的迷宫</param>
    Maze(int width, int height, MazeType type = MazeType::GENERATED, const std::vector<std::vector<char>>& providedMaze = {});

    /// <summary>
    /// 生成迷宫
    /// </summary>
    void generateMaze();

    /// <summary>
    /// 显示迷宫
    /// </summary>
    void displayMaze() const;

    /// <summary>
    /// 移动玩家
    /// </summary>
    /// <param name="direction">移动方向</param>
    int move(char direction);

    /// <summary>
    /// 检查玩家是否到达终点
    /// </summary>
    /// <returns>如果到达终点，则返回 true；否则返回 false</returns>
    bool isAtExit() const;

private:
    int width; ///< 迷宫的宽度
    int height; ///< 迷宫的高度
    std::vector<std::vector<char>> maze; ///< 迷宫的二维数组
    int playerX; ///< 玩家当前的 X 坐标
    int playerY; ///< 玩家当前的 Y 坐标

    /// <summary>
    /// 初始化迷宫
    /// </summary>
    void initializeMaze();

    /// <summary>
    /// 挖掘路径
    /// </summary>
    /// <param name="x">当前 X 坐标</param>
    /// <param name="y">当前 Y 坐标</param>
    void carvePath(int x, int y);

    /// <summary>
    /// 检查移动是否有效
    /// </summary>
    /// <param name="x">目标 X 坐标</param>
    /// <param name="y">目标 Y 坐标</param>
    /// <returns>如果移动有效，则返回 true；否则返回 false</returns>
    bool isValidMove(int x, int y) const;
};

#endif // MAZE_H