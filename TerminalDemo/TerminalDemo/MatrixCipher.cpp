#include "MatrixCipher.h"

// 构造函数实现
MatrixCipher::MatrixCipher(int size)
    : size(size), matrix(size + 1, std::vector<int>(size + 1)), randomArray(size + 1) {
    srand(static_cast<unsigned int>(time(nullptr))); // 初始化随机数生成器
    generateMatrix(); // 生成矩阵
    generateRandomArray(size); // 生成密钥数组
}

// 生成随机数填充矩阵
void MatrixCipher::generateMatrix() {
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            matrix[i][j] = rand() % 99 + 1; // 生成1-99之间的随机数
        }
    }
}

// 生成随机数填充密钥数组
void MatrixCipher::generateRandomArray(int size) {
    for (int i = 1; i <= size; i++) {
        randomArray[i] = rand() % size + 1; // 生成1到size之间的随机数
    }
}

// 打印加密矩阵
void MatrixCipher::displayMatrix() {
    std::cout << "加密矩阵:" << std::endl;
    std::cout << "     "; // 为行号预留空间
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
    for (int j = 1; j <= size; j++) {
        std::cout << std::setw(4) << j;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << std::endl;

    for (int i = 1; i <= size; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << std::setw(4) << i << " ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        for (int j = 1; j <= size; j++) {
            std::cout << std::setw(4) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

void MatrixCipher::displayKey() {
    std::cout << "\n密钥:" << std::endl;
    int t = size, towards = 0, m = 1;

    while (t > 0) {
        int index = size + 1 - t; // 计算索引
        if (index >= 1 && index <= randomArray.size()) { // 确保索引在有效范围内
            if (towards == 0) {
                std::cout << std::setw(4) << matrix[m][randomArray[index]];
                m = randomArray[index];
                t--;
                towards = 1;
            }
            else {
                std::cout << std::setw(4) << matrix[randomArray[index]][m];
                m = randomArray[index];
                t--;
                towards = 0;
            }
        }
        else {
            std::cerr << "密钥数组索引越界" << std::endl;
            return;
        }
    }
    std::cout << std::endl;
}

// 进行破译操作
int MatrixCipher::decipher() {
    int t = 1;
    int times = 0;
    int number;

    while (t <= size) {
        std::cout << "请输入第" << t << "个数:";
        std::cin >> number;
        if (number != randomArray[t]) {
            times++;
            std::cout << "破译失败,重新输入剩余" << 3 - times << "机会";
            if (times == 3) {
                std::cout << "很遗憾破译失败";
                return 0;
            }
        }
        else {
            t++;
        }
        if (t == size+1) {
            std::cout << "成功破译";
            return 1;
        }
    }
    std::cout << std::endl;
}