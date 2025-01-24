#include "TerminalMockup.h"
#include "Maze.h"
#include "TextTerminal.h"
#include "CountdownWindow.h"

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
    std::string pathStr = path.string();

    // 如果路径以初始路径开头，替换为 "~"
    if (pathStr.find(currentPathStr) == 0) {
        pathStr.replace(0, currentPathStr.length(), "~");
    }

    // 替换反斜杠为正斜杠（跨平台显示友好）
    std::replace(pathStr.begin(), pathStr.end(), '\\', '/');

    return pathStr;
}

// 构造函数，初始化命令映射和当前路径
TerminalMockup::TerminalMockup(const std::string& initialPath) {
    // 如果用户未提供路径，使用当前工作目录
    if (initialPath.empty()) {
        currentPath = std::filesystem::current_path();
    }
    else {
        currentPath = std::filesystem::absolute(std::filesystem::path(initialPath));
    }

    std::filesystem::current_path(currentPath); // 设置当前工作目录
    currentPathStr = currentPath.string(); // 保存初始路径字符串

    // 初始化命令映射
    commands["ls"] = &TerminalMockup::command_ls;
    commands["echo"] = &TerminalMockup::command_echo;
    commands["cat"] = &TerminalMockup::command_cat;
    commands["cd"] = &TerminalMockup::command_cd;
    commands["hack"] = &TerminalMockup::command_hack;
}

// 自动补全函数
std::string TerminalMockup::autocomplete(const std::string& input) {
    // 找到第一个空格，分离命令和参数
    size_t spacePos = input.find(' ');
    std::string command = (spacePos == std::string::npos) ? input : input.substr(0, spacePos);
    std::string args = (spacePos == std::string::npos) ? "" : input.substr(spacePos + 1);

    // 如果参数为空，则只处理命令补全
    if (args.empty()) {
        return autocompleteCommand(command);
    }

    // 对参数部分进行路径补全
    std::string completedPath = autocompletePath(args);
    return command + " " + completedPath; // 保留命令部分
}

// 命令补全
std::string TerminalMockup::autocompleteCommand(const std::string& command) {
    std::vector<std::string> commandMatches;

    // 遍历所有命令，查找匹配项
    for (const auto& cmd : commands) {
        if (cmd.first.find(command) == 0) {
            commandMatches.push_back(cmd.first);
        }
    }

    // 如果只有一个匹配项，直接返回
    if (commandMatches.size() == 1) {
        return commandMatches[0];
    }
    else if (commandMatches.size() > 1) {
        // 如果有多个匹配项，显示所有可能的选项
        std::cout << "\n可能的命令选项:\n";
        for (const auto& match : commandMatches) {
            std::cout << match << "\n";
        }
    }

    return command; // 返回原命令
}

// 文件补全
std::string TerminalMockup::autocompletePath(const std::string& input) {
    std::filesystem::path searchPath = currentPath / input;
    std::string baseName = searchPath.filename().string();
    std::filesystem::path dirPath = searchPath.parent_path().empty() ? currentPath : searchPath.parent_path();

    // 遍历目录查找匹配项
    std::vector<std::string> matches;
    for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
        std::string filename = entry.path().filename().string();
        if (filename.find(baseName) == 0) { // 检查文件名前缀是否匹配
            matches.push_back(filename);
        }
    }

    // 如果有多个匹配项，显示所有可能的选项
    if (matches.size() > 1) {
        std::cout << "\n可能的补全选项:\n";
        for (const auto& match : matches) {
            std::cout << match << "\n";
        }
        return input; // 返回原输入，让用户自行选择
    }
    else if (matches.size() == 1) {
        // 如果只有一个匹配项，补全它
        return input + matches[0].substr(baseName.length());
    }

    return input; // 如果没有匹配项，返回原输入
}

// 启动终端模拟
void TerminalMockup::run() {
    std::string input;

    while (true) {
        std::cout << formatPath(currentPath, currentPathStr) << " $ ";
        char ch;
        input.clear();

        while ((ch = _getch()) != '\r') {
            if (ch == '\t') {
                input = autocomplete(input);
                std::cout << "\r" << formatPath(currentPath, currentPathStr) << " $ " << input;
            }
            else if (ch == '\b') {
                if (!input.empty()) {
                    input.pop_back();
                    std::cout << "\r" << formatPath(currentPath, currentPathStr) << " $ " << input << " ";
                }
            }
            else {
                input += ch;
                std::cout << ch;
            }
        }

        if (input == "exit") {
            break;
        }

        executeCommand(input);
    }
}

void TerminalMockup::findBoss()
{
    boss = 1;
}

// 执行输入的命令
void TerminalMockup::executeCommand(const std::string& input) {
    std::istringstream iss(input); // 创建输入流
    std::string command; // 存储命令
    iss >> command; // 获取命令

    std::string args; // 存储命令参数
    std::getline(iss, args); // 获取命令参数

    std::cout << "\n";
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

// utf-8转GBK
std::string UTF8ToGBK(const std::string& utf8Str) {
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, nullptr, 0);
    if (len <= 0) return "";

    std::wstring wideStr(len, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, &wideStr[0], len);

    len = WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (len <= 0) return "";

    std::string gbkStr(len, 0);
    WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), -1, &gbkStr[0], len, nullptr, nullptr);

    return gbkStr;
}

// 模拟cat
void TerminalMockup::command_cat(const std::string& args) {
    std::string trimmedArgs = trim(args); // 去除前后空白
    std::filesystem::path filePath = currentPath / trimmedArgs; // 组合路径
    std::cout << "尝试打开: " << filePath << std::endl; // 调试输出

    std::ifstream file(filePath, std::ios::binary); // 二进制模式打开文件
    if (file) {
        std::string fileContent((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());

        // 检测文件是否包含 UTF-8 BOM
        if (fileContent.size() >= 3 &&
            static_cast<unsigned char>(fileContent[0]) == 0xEF &&
            static_cast<unsigned char>(fileContent[1]) == 0xBB &&
            static_cast<unsigned char>(fileContent[2]) == 0xBF) {
            // 文件为 UTF-8，移除 BOM
            fileContent = fileContent.substr(3);

            // 转换为 GBK 并输出
            std::string gbkContent = UTF8ToGBK(fileContent);
            std::cout << gbkContent << std::endl;
        }
        else {
            // 假设文件为 GBK，直接输出
            std::cout << fileContent << std::endl;
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

void TerminalMockup::command_hack(const std::string& args) {
    if (!boss) {
        std::cout << "Command not found: hack" << std::endl; // 未找到命令
    }
    else {
        std::vector<std::vector<char>> providedMaze = { 
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}, 
            {'#', '@', ' ', ' ', '$', '#', ' ', ' ', ' ', ' ', '#'}, 
            {'#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#'}, 
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'}, 
            {'#', '*', '#', '#', '#', '#', '#', '#', ' ', '#', '#'}, 
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', '#'}, 
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} }; 
        int width = 11; 
        int height = 7; 
        char command;
        Maze maze2(width, height, MazeType::PROVIDED, providedMaze); 
        std::vector<std::wstring> lines = {
        L"快进攻服务系统",
        L"没有时间了"
        };

        CountdownWindow time(360);

        TextTerminal text(lines);
        text.run();
        std::thread targetThread(&CountdownWindow::Run, &time);
        while (time.flag) {
            system("cls");
            maze2.displayMaze();
            std::cout << "移动方向 (w: 上, s: 下, a: 左, d: 右, q: 退出): ";
            command = _getch(); // 使用 _getch() 获取单个字符输入 
            if (maze2.move(command)) {
                time.flag = 0;
                break;
            }
        }   
    }
}