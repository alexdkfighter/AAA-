#ifndef TERMINALMOCKUP_H
#define TERMINALMOCKUP_H

#include "cmd_print.h"

class TerminalMockup {
public:
    TerminalMockup(const std::string& initialPath); // 构造函数，带初始路径
    void run(); // 启动终端模拟

    void findBoss(); // 允许boss战命令

private:
    void executeCommand(const std::string& input); // 执行输入的命令
    void command_ls(const std::string& args); // 模拟 ls 命令
    void command_echo(const std::string& args); // 模拟 echo 命令
    void command_cat(const std::string& args); // 模拟 cat 命令
    void command_cd(const std::string& args); // 模拟 cd 命令
    void command_hack(const std::string& args); // boss战开始指令

    std::string autocomplete(const std::string& input); // 自动补全
    std::string autocompleteCommand(const std::string& command); // 命令补全
    std::string autocompletePath(const std::string& input); //补全文件
    std::map<std::string, void (TerminalMockup::*)(const std::string&)> commands; // 命令映射
    std::filesystem::path currentPath; // 当前工作目录
    std::string currentPathStr; // 初始工作目录
    int boss = 0; // 记录boss战是否允许
};

#endif // TERMINALMOCKUP_H