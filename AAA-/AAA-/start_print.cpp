#include "start_print.h"
#include <iostream>
#include <windows.h>//����Sleep����

//���캯��
start_print::start_print(){}

//��ͷ��ģ���ն�������ʾ
void start_print::start_show()
{
    std::cout << "Starting by Ubuntu ......" << "\n";
    std::cout << "Opening the image from AAA- ..." << "\n";
    Sleep(500);
    std::cout << "ldd (Debian GLIBC 2.40-3) 2." << "\n";
    std::cout << "Copyright(C) 2024 Free Software Foundation, Inc." << "\n";
    std::cout << "This is free software; see the source for copying conditions. There is NO" << "\n";
    std::cout << "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE." << "\n";
    std::cout << "Written by Roland McGrath and Ulrich Drepper." << "\n";
    Sleep(500);

    std::cout << "Loading shared libraries..." << "\n";
    std::cout << "  libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6" << "\n";
    std::cout << "  /lib64/ld-linux-x86-64.so.2 => /lib64/ld-linux-x86-64.so.2" << "\n";
    std::cout << "Initializing system services..." << "\n";
    std::cout << "  Network services starting..." << "\n";
    std::cout << "  File system checks complete." << "\n";
    std::cout << "Welcome to Ubuntu 20.04 LTS!" << "\n";
    std::cout << "System information as of " << __DATE__ << " " << __TIME__ << "\n";

    std::cout << "User: Kevin Mitnick" << "\n"; // Replace with actual user name
    std::cout << "Kernel version: 5.4.0-42-generic" << "\n"; // Example kernel version
    Sleep(600);
}

void start_print::menu() {
    std::cout << R"(
                                                             
  ,----..     ,--,                                 ,---,     
 /   /   \  ,--.'|                               ,--.' |     
|   :     : |  | :                               |  |  :     
.   |  ;. / :  : '                    .--.--.    :  :  :     
.   ; /--`  |  ' |       ,--.--.     /  /    '   :  |  |,--. 
;   | ;     '  | |      /       \   |  :  /`./   |  :  '   | 
|   : |     |  | :     .--.  .-. |  |  :  ;_     |  |   /' : 
.   | '___  '  : |__    \__\/: . .   \  \    `.  '  :  | | | 
'   ; : .'| |  | '.'|   ," .--.; |    `----.   \ |  |  ' | : 
'   | '/  : ;  :    ;  /  /  ,.  |   /  /`--'  / |  :  :_:,' 
|   :    /  |  ,   /  ;  :   .'   \ '--'.     /  |  | ,'     
 \   \ .'    ---`-'   |  ,     .-./   `--'---'   `--''       
  `---`                `--`---'                              
    )" << std::endl;
    std::cout << "\n" << "\n";
    std::cout << "�������֣�ѡ����Ҫ��ʲô\n";
    std::cout << "1������\n";
    std::cout << "2�����ؼ���\n";
    std::cout << "3���˳�\n";
}