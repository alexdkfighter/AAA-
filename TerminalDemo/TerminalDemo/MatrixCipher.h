#ifndef MATRIXCIPHER_H
#define MATRIXCIPHER_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <windows.h>

class MatrixCipher {
private:
    int size; // 矩阵大小
    std::vector<std::vector<int>> matrix; // 加密矩阵
    std::vector<int> randomArray; // 密钥数组

    // 生成随机数填充矩阵
    void generateMatrix();

    // 生成随机数填充密钥数组
    void generateRandomArray(int size);

public:
    // 构造函数，初始化随机数生成器并生成矩阵和密钥
    MatrixCipher(int size);

    // 打印加密矩阵
    void displayMatrix();

    // 打印密钥
    void displayKey();

    // 进行破译操作
    int decipher();
};

#endif // MATRIXCIPHER_H