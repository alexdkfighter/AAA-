#include "cmd_print.h"

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void updateLine(int line, const std::string& text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = 0; // �ӵ�һ�п�ʼ
    coord.Y = line - 1; // ������0��ʼ�����Լ�1

    // �ƶ���굽ָ��λ��
    SetConsoleCursorPosition(hConsole, coord);

    // �����ǰ��
    std::cout << std::string(80, ' '); // ������Ϊ80��
    SetConsoleCursorPosition(hConsole, coord); // �ٴ��ƶ���굽��ʼλ��

    // ���������
    std::cout << text;
    std::cout.flush(); // ˢ�����
}

void showGarbledText(int line, int color, const std::string& text, int& running, int garbledDuration, int clearDuration, std::mt19937& rng) {
    // ��������
    std::string garbledText;
    for (size_t i = 0; i < text.size(); ++i) {
        garbledText += static_cast<char>(rng() % 256); // ��������ַ�
    }

    while (running) {
        // ��ʾ����
        for (size_t i = 0; i < garbledText.size(); ++i) {
            int randomColor = rng() % 15 + 1; // �����ɫ (1-15)
            setColor(randomColor);
            std::string garbledText;
            for (size_t i = 0; i < text.size(); ++i) {
                garbledText += static_cast<char>(rng() % 256); // ��������ַ�
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // �ӳ�����ʾЧ��
        }

        // �ָ���ʾ����
        setColor(color); // ����Ĭ����ɫ
        updateLine(line, text);
        std::this_thread::sleep_for(std::chrono::milliseconds(clearDuration));

        // ����Ƿ�ֹͣ
        if (running == 0) {
            break; // ��� running Ϊ 0���˳�ѭ��
        }

        // �ٴ���ʾ����
        for (size_t i = 0; i < garbledText.size(); ++i) {
            int randomColor = rng() % 15 + 1; // �����ɫ (1-15)
            setColor(randomColor);
            std::string garbledText;
            for (size_t i = 0; i < text.size(); ++i) {
                garbledText += static_cast<char>(rng() % 256); // ��������ַ�
            }
            updateLine(line, garbledText.substr(0, i + 1)); // �����ʾ�ַ�
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // �ӳ�����ʾЧ��
        }
    }

    // �����ʾ����
    setColor(color); // ����Ĭ����ɫ
    updateLine(line, text);
}

void startGarbledTextThread(int line, int color, const std::string& text, int& running, int garbledDuration, int clearDuration) {
    // ���������������
    std::random_device rd; // ��ȡ����豸
    std::mt19937 rng(rd()); // ʹ������豸��ʼ��÷ɭ��ת�㷨

    std::thread garbledThread(showGarbledText, line, color, text, std::ref(running), garbledDuration, clearDuration, std::ref(rng));
    garbledThread.detach(); // �����̣߳�ʹ���ں�̨����
}