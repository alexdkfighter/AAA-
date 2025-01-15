#include "Maze.h"

Maze::Maze(int w, int h) : width(w), height(h), playerX(1), playerY(1) {
    srand(static_cast<unsigned int>(time(0))); // 设置随机数种子
    initializeMaze(); // 初始化迷宫
    generateMaze(); // 生成迷宫
    maze[height - 2][width - 2] = 'E'; // 设置终点
    maze[playerY][playerX] = '@'; // 设置起点
}

void Maze::initializeMaze() {
    maze.resize(height, std::vector<char>(width, '#')); // 用墙壁填充迷宫
}

void Maze::generateMaze() {
    carvePath(1, 1); // 从 (1, 1) 开始挖掘路径
}

void Maze::carvePath(int x, int y) {
    maze[y][x] = ' '; // 标记当前单元为路径

    // 随机打乱方向
    std::vector<std::pair<int, int>> directions = {
        {2, 0}, {-2, 0}, {0, 2}, {0, -2}
    };

    std::random_device rd; // 随机数种子
    std::mt19937 g(rd()); // 随机数生成器

    std::shuffle(directions.begin(), directions.end(), g); // 使用 std::shuffle 打乱方向

    for (const auto& dir : directions) {
        int newX = x + dir.first; // 新的X坐标
        int newY = y + dir.second; // 新的Y坐标

        if (newX > 0 && newX < width && newY > 0 && newY < height && maze[newY][newX] == '#') {
            maze[y + dir.second / 2][x + dir.first / 2] = ' '; // 挖掘墙壁
            carvePath(newX, newY); // 递归挖掘下一个单元
        }
    }
}

bool Maze::isValidMove(int x, int y) const {
    return (x > 0 && x < width && y > 0 && y < height && maze[y][x] != '#'); // 检查移动是否合法
}

void Maze::displayMaze() const {
    for (const auto& row : maze) {
        for (char cell : row) {
            std::cout << cell; // 输出每个单元
        }
        std::cout << std::endl; // 换行
    }
}

void Maze::move(char direction) {
    int newX = playerX; // 新的X坐标
    int newY = playerY; // 新的Y坐标

    switch (direction) {
    case 'w': newY--; break; // 上
    case 's': newY++; break; // 下
    case 'a': newX--; break; // 左
    case 'd': newX++; break; // 右
    case 'q': exit(0); // 强制退出
    default: return; // 无效输入
    }

    if (isValidMove(newX, newY)) {
        maze[playerY][playerX] = ' '; // 清除旧位置
        playerX = newX; // 更新玩家X坐标
        playerY = newY; // 更新玩家Y坐标
        maze[playerY][playerX] = '@'; // 更新新位置

        if (isAtExit()) {
            std::cout << "恭喜你到达终点！" << std::endl; // 到达终点时输出消息
            exit(0); // 结束程序
        }
    }
}

bool Maze::isAtExit() const {
    return (playerX == width - 2 && playerY == height - 2); // 检查是否到达终点
}