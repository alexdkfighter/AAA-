#include "TerminalMockup.h"

// 去除字符串前后的空格
std::string trim(const std::string& str) {
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        ++start;
    }
    auto end = str.end();
    do {
        --end;
    } while (end != start && std::isspace(*end));
    return std::string(start, end + 1);
}

// 格式化路径
std::string formatPath(const std::filesystem::path& path, const std::string& currentPathStr) {

    char* homeDir = nullptr;
    size_t size = 0;

    // 如果路径以 currentPathStr 开头，则替换为 ~
    if (path.string().find(currentPathStr) == 0) {
        std::string pathStr = path.string();
        pathStr.replace(0, currentPathStr.length(), "~");
        std::replace(pathStr.begin(), pathStr.end(), '\\', '/');
        return pathStr;
    }

    // 路径以.开头也更改
    if (path.string().find(".") == 0) {
        std::string pathStr = path.string();
        pathStr.replace(0, 1, "~");
        std::replace(pathStr.begin(), pathStr.end(), '\\', '/');
        return pathStr;
    }

    return path.string();
}

// 构造函数，初始化命令映射和当前路径
TerminalMockup::TerminalMockup(const std::string& initialPath) : currentPath(initialPath) {
    commands["ls"] = &TerminalMockup::command_ls; // 关联 ls 命令
    commands["echo"] = &TerminalMockup::command_echo; // 关联 echo 命令
    commands["cat"] = &TerminalMockup::command_cat; // 关联 cat 命令
    commands["cd"] = &TerminalMockup::command_cd; // 映射 cd 命令

    std::filesystem::current_path(currentPath); // 设置当前工作目录
    // 将路径转换为字符串，并记录为初始路径
    currentPathStr = std::filesystem::current_path().string();
}

// 启动终端模拟
void TerminalMockup::run() {
    std::string input; // 存储用户输入
    while (true) {
        std::cout << formatPath(currentPath, currentPathStr) << " $ "; // 提示符显示当前路径
        std::getline(std::cin, input); // 获取用户输入

        if (input == "exit") {
            break; // 如果输入 "exit"，则退出
        }

        executeCommand(input); // 执行输入的命令
    }
}

// 执行输入的命令
void TerminalMockup::executeCommand(const std::string& input) {
    std::istringstream iss(input); // 创建输入流
    std::string command; // 存储命令
    iss >> command; // 获取命令

    std::string args; // 存储命令参数
    std::getline(iss, args); // 获取命令参数

    auto it = commands.find(command); // 查找命令
    if (it != commands.end()) {
        (this->*(it->second))(args); // 调用对应的命令函数并传递参数
    }
    else {
        std::cout << "Command not found: " << command << std::endl; // 未找到命令
    }
}

// 模拟 ls 命令，列出当前目录的文件
void TerminalMockup::command_ls(const std::string& args) {
    for (const auto& entry : std::filesystem::directory_iterator(currentPath)) {
        std::cout << entry.path().filename().string() << std::endl; // 输出文件名
    }
}

// 模拟 echo 命令，直接输出参数
void TerminalMockup::command_echo(const std::string& args) {
    std::cout << args << std::endl; // 直接输出参数
}

// 模拟 cat 命令，输出文件的内容
void TerminalMockup::command_cat(const std::string& args) {
    std::string trimmedArgs = trim(args); // 去除前后空白
    std::filesystem::path filePath = currentPath / trimmedArgs; // 组合路径
    std::cout << "尝试打开: " << filePath << std::endl; // 调试输出

    std::ifstream file(filePath); // 打开文件
    if (file) {
        std::string line; // 存储每一行
        while (std::getline(file, line)) {
            std::cout << line << std::endl; // 输出文件内容
        }
    }
    else {
        std::cout << "没有这样的文件: " << trimmedArgs << std::endl; // 文件不存在
    }
}

void TerminalMockup::command_cd(const std::string& args) {
    std::string trimmedArgs = trim(args); // 去除前后空格
    std::filesystem::path newPath = currentPath / trimmedArgs; // 构造新的路径

    std::cout << "尝试更改路径到: " << formatPath(newPath, currentPathStr) << std::endl;

    // 检查路径是否存在且是目录
    if (std::filesystem::exists(newPath) && std::filesystem::is_directory(newPath)) {
        std::filesystem::path newCurrentPath = std::filesystem::absolute(newPath);
        if (formatPath(newCurrentPath, currentPathStr).find('~') != std::string::npos) {
            currentPath = newCurrentPath; // 获取绝对路径
            std::cout << "当前路径已更改为: " << formatPath(currentPath, currentPathStr) << std::endl; // 格式化输出
        }
        else {
            std::cout << "已到达根目录" << std::endl;
        }
    }
    else {
        std::cout << "错误: 目录不存在: " << trimmedArgs << std::endl;
    }
}