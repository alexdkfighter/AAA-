#include "game.h"

// 构造函数实现
game::game(int progress, const std::vector<std::string>& ips) {
    // 获取本机 IP 地址
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return;
    }

    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        std::cerr << "gethostname failed." << std::endl;
        WSACleanup();
        return;
    }

    struct addrinfo hints, * res;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, NULL, &hints, &res) != 0) {
        std::cerr << "getaddrinfo failed." << std::endl;
        WSACleanup();
        return;
    }

    for (struct addrinfo* p = res; p != nullptr; p = p->ai_next) {
        char ipstr[INET_ADDRSTRLEN];
        struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
        inet_ntop(p->ai_family, &(ipv4->sin_addr), ipstr, sizeof(ipstr));
        terminal.ip = ipstr; // 设置 IP 地址
        break; // 只获取第一个 IP 地址
    }

    freeaddrinfo(res);
    WSACleanup();

    terminal.levelProgress = progress; // 设置关卡进度
    terminal.connectableIPs = ips; // 设置可连接的 IP 地址
}

// 获取 IP 地址
std::string game::getIP() const {
    return terminal.ip;
}

// 获取关卡进度
int game::getLevelProgress() const {
    return terminal.levelProgress;
}

// 获取可连接 IP 字符串组
std::vector<std::string> game::getConnectableIPs() const {
    return terminal.connectableIPs;
}

// 运行终端
void game::runTerminal() {
    mockup.run(); // 调用 TerminalMockup 的 run 方法
}
