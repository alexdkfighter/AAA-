#include "MatrixCipher.h"

int main() {
    int size;

    std::cout << "请输入矩阵大小 (例如 8): ";
    std::cin >> size;
    if (size <= 0) {
        std::cerr << "矩阵大小必须大于0" << std::endl;
        return 1;
    }

    MatrixCipher cipher(size); // 创建MatrixCipher对象
    cipher.displayMatrix(); // 显示加密矩阵
    cipher.displayKey(); // 显示密钥

    std::cout << cipher.decipher(); // 进行破译操作

    return 0;
}