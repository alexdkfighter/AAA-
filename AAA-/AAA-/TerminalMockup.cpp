#include "TerminalMockup.h"

// 构造函数，初始化命令映射
TerminalMockup::TerminalMockup() {
    commands["ls"] = &TerminalMockup::command_ls;          // 关联 ls 命令
    commands["echo"] = &TerminalMockup::command_echo;      // 关联 echo 命令
}

// 启动终端模拟
void TerminalMockup::run() {
    std::string input;
    while (true) {
        std::cout << "$ ";  // 提示符
        std::getline(std::cin, input);

        // 如果输入 "exit"，则退出
        if (input == "exit") {
            break;
        }

        executeCommand(input); // 执行输入的命令
    }
}

// 执行输入的命令
void TerminalMockup::executeCommand(const std::string& input) {
    std::istringstream iss(input);
    std::string command;
    iss >> command; // 获取命令

    std::string args;
    std::getline(iss, args); // 获取命令参数

    // 查找命令并执行相应的处理函数
    auto it = commands.find(command);
    if (it != commands.end()) {
        // 调用对应的命令函数并传递参数
        (this->*(it->second))(args);
    }
    else {
        std::cout << "Command not found: " << command << std::endl; // 未找到命令
    }
}

// 模拟 ls 命令，接受参数但不使用
void TerminalMockup::command_ls(const std::string& args) {
    std::cout << "file1.txt\nfile2.txt\ndir1\n";  // 示例输出
}

// 模拟 echo 命令，直接输出参数
void TerminalMockup::command_echo(const std::string& args) {
    std::cout << args << std::endl; // 直接输出参数
}