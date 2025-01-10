#pragma once
#include "cmd_print.h"
#include "TerminalMockup.h"

#pragma comment(lib, "ws2_32.lib")

class game
{
public:
    struct TerminalInfo
    {
        std::string username = "D"; // 用户名
        std::string ip; // IP 地址
        int levelProgress = 0; // 关卡进度，默认值为0
        std::vector<std::string> connectableIPs; // 可连接 IP 的字符串组
    };

private:
    TerminalInfo terminal;

public:
    // 构造函数，要求给 struct 赋值
    game(int progress = 0, const std::vector<std::string>& ips = {"127.0.0.1"});

    // 获取 IP 地址
    std::string getIP() const;

    // 获取关卡进度
    int getLevelProgress() const;

    // 获取可连接 IP 字符串组
    std::vector<std::string> getConnectableIPs() const;

    // 运行终端
    void runTerminal(std::string initialPath);

    // 其他成员函数可以在这里添加
};