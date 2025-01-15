#include "Maze.h"

Maze::Maze(int w, int h, MazeType type, const std::vector<std::vector<char>>& providedMaze)
    : width(w), height(h), playerX(1), playerY(1) {
    srand(static_cast<unsigned int>(time(0)));
    initializeMaze();

    if (type == MazeType::GENERATED) {
        generateMaze();
    }
    else if (type == MazeType::PROVIDED) {
        maze = providedMaze;
    }

    maze[playerY][playerX] = '@'; // 设置玩家初始位置
    maze[height - 2][width - 2] = 'E'; // 设置终点
}

void Maze::initializeMaze() {
    maze.resize(height, std::vector<char>(width, '#')); // 用墙壁填充迷宫
}

void Maze::generateMaze() {
    carvePath(1, 1); // 从 (1, 1) 开始挖掘路径
}

void Maze::carvePath(int x, int y) {
    maze[y][x] = ' '; // 标记当前单元为路径
    std::vector<std::pair<int, int>> directions = {
        {2, 0}, {-2, 0}, {0, 2}, {0, -2}
    };

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(directions.begin(), directions.end(), g);

    for (const auto& dir : directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;

        if (newX > 0 && newX < width && newY > 0 && newY < height && maze[newY][newX] == '#') {
            maze[y + dir.second / 2][x + dir.first / 2] = ' ';
            carvePath(newX, newY);
        }
    }
}

bool Maze::isValidMove(int x, int y) const {
    return (x > 0 && x < width && y > 0 && y < height && maze[y][x] != '#');
}

void Maze::displayMaze() const {
    for (const auto& row : maze) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}

// 强制退出返回-1，无效输入返回0，到终点返回1
int Maze::move(char direction) {
    int newX = playerX;
    int newY = playerY;

    switch (direction) {
    case 'w': newY--; break; // 上
    case 's': newY++; break; // 下
    case 'a': newX--; break; // 左
    case 'd': newX++; break; // 右
    case 'q': return -1; // 强制退出
    default: return 0; // 无效输入
    }

    if (isValidMove(newX, newY)) {
        maze[playerY][playerX] = ' '; // 清除旧位置
        playerX = newX;
        playerY = newY;
        maze[playerY][playerX] = '@'; // 更新新位置

        if (isAtExit()) {
            std::cout << "恭喜你到达终点！" << std::endl;
            return 1;
        }
    }
}

bool Maze::isAtExit() const {
    return (playerX == width - 2 && playerY == height - 2);
}