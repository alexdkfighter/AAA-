#include "cmd_print.h"

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void updateLine(int line, const std::string& text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = 0; // 从第一列开始
    coord.Y = line - 1; // 行数从0开始，所以减1

    // 移动光标到指定位置
    SetConsoleCursorPosition(hConsole, coord);

    // 清除当前行
    std::cout << std::string(80, ' '); // 假设宽度为80列
    SetConsoleCursorPosition(hConsole, coord); // 再次移动光标到起始位置

    // 输出新内容
    std::cout << text;
    std::cout.flush(); // 刷新输出
}

void showGarbledText(int line, int color, const std::string& text, int& running, int garbledDuration, int clearDuration, std::mt19937& rng) {
    // 生成乱码
    std::string garbledText;
    for (size_t i = 0; i < text.size(); ++i) {
        garbledText += static_cast<char>(rng() % 256); // 生成随机字符
    }

    while (running) {
        // 显示乱码
        for (size_t i = 0; i < garbledText.size(); ++i) {
            int randomColor = rng() % 15 + 1; // 随机颜色 (1-15)
            setColor(randomColor);
            std::string garbledText;
            for (size_t i = 0; i < text.size(); ++i) {
                garbledText += static_cast<char>(rng() % 256); // 生成随机字符
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 延迟以显示效果
        }

        // 恢复显示明文
        setColor(color); // 设置默认颜色
        updateLine(line, text);
        std::this_thread::sleep_for(std::chrono::milliseconds(clearDuration));

        // 检查是否停止
        if (running == 0) {
            break; // 如果 running 为 0，退出循环
        }

        // 再次显示乱码
        for (size_t i = 0; i < garbledText.size(); ++i) {
            int randomColor = rng() % 15 + 1; // 随机颜色 (1-15)
            setColor(randomColor);
            std::string garbledText;
            for (size_t i = 0; i < text.size(); ++i) {
                garbledText += static_cast<char>(rng() % 256); // 生成随机字符
            }
            updateLine(line, garbledText.substr(0, i + 1)); // 逐个显示字符
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 延迟以显示效果
        }
    }

    // 最后显示明文
    setColor(color); // 设置默认颜色
    updateLine(line, text);
}

void startGarbledTextThread(int line, int color, const std::string& text, int& running, int garbledDuration, int clearDuration) {
    // 设置随机数生成器
    std::random_device rd; // 获取随机设备
    std::mt19937 rng(rd()); // 使用随机设备初始化梅森旋转算法

    std::thread garbledThread(showGarbledText, line, color, text, std::ref(running), garbledDuration, clearDuration, std::ref(rng));
    garbledThread.detach(); // 分离线程，使其在后台运行
}