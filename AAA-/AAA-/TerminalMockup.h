#pragma once
#include "cmd_print.h"  // 假设这是用于输出的头文件

// TerminalMockup 类用于模拟一个虚拟的 Linux 终端
class TerminalMockup {
public:
    // 构造函数
    TerminalMockup();

    // 启动终端模拟
    void run();

private:
    // 定义命令函数指针类型，接受参数
    using CommandFunction = void (TerminalMockup::*)(const std::string&);

    // 存储命令与其对应处理函数的映射
    std::map<std::string, CommandFunction> commands;

    // 执行输入的命令
    void executeCommand(const std::string& input);

    // 模拟 ls 命令，接受参数但不使用
    void command_ls(const std::string& args);

    // 模拟 echo 命令，接受参数
    void command_echo(const std::string& args);
};